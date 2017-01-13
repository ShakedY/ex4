#include "Client.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#define BUFFSIZE 32768

using namespace std;
using namespace boost::archive;

Client::Client(int argc, char* argv[])
{
	// Create a socket to run on the entered id adress and port.
	// because it's not a server, no need to bind.
 	mySocket = new Tcp(0, atoi(argv[2]),argv[1]);
 	//Set all pointers to be NULL at first.
	driver = NULL;
	cab = NULL;
	trip = NULL;
	//Initialize the socket.
	mySocket->initialize();

	//Start creating the driver and communication process.
	buildDriver();
}

Client::~Client()
{
	//Delete driver and cab.The driver will delete the trip by itself.
	delete driver;
	delete cab;
	//Call socket's destructor to close it.
	delete mySocket;
}

void Client::run()
{
	//Run a switch on the action that we will get from the server.
	char action = -1;
	do
	{
		//Receive an action from the server which is one byte.
		mySocket->reciveData(&action, 1);
		switch (action)
		{
			case moveOneStep:
				//Server moved the driver one step so our driver will move as well.
				driver->moveOneStep();
				break;
			case setTrip:
				//Server tells us it will send us a new trip,run getTripFromServer function.
				getTripFromServer();
				break;
			case shutDown:
				//Server told us to shutDown so break from this switch.
				break;
			default:
				// no such operator
				break;
		}
	} while (action != shutDown);
	//ACK tell server we got everything.
	mySocket->sendData('a');
}

void Client::buildDriver()
{
	string serial_str;
	int id, cabId, age, yearsOfExperience, bytes;
	char buffer[BUFFSIZE], stat;
	
	//-------------------------get driver's members as input---------------
	scanf("%d,%d,%c,%d,%d", &id, &age, &stat, &yearsOfExperience, &cabId);
	driver = new Driver(id, age, stat, yearsOfExperience, NULL, NULL);

	//---------------------------serializing the driver--------------------
	this->serializeObj<Driver>(&serial_str, driver);

	// Send serialized string through the socket.
	mySocket->sendData(serial_str);

	// Now the client will wait to receive the cab from the server.
	bytes = mySocket->reciveData(buffer, BUFFSIZE);
	cab = deSerializeObj<Cab>(buffer, bytes);
	driver->setCab(cab);
	// Get action of setTrip from server before setting the trip.
	mySocket->reciveData(buffer, 1);
	//Get the trip from the server.
	getTripFromServer();
}

void Client::getTripFromServer()
{
	// Now the client will wait to receive the trip from the server.
	char buffer[BUFFSIZE];
	int bytes = mySocket->reciveData(buffer, BUFFSIZE);
	// -1 because the socket added '\0' at the end
	trip = deSerializeObj<Trip>(buffer, bytes);
	driver->setTrip(trip);
}


template<class T>
void Client::serializeObj(std::string* serial_str, T* obj)
{
	//Serialize the object using recitation examples.
	boost::iostreams::back_insert_device<std::string> inserter(*serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
			inserter);
	boost::archive::binary_oarchive oa(s);
	oa << obj;
	s.flush();
}

template<class T>
T* Client::deSerializeObj(const char* serial_str, int size)
{
	T* obj;
	//Deserialize same as recitation examples.
	boost::iostreams::basic_array_source<char> device(serial_str, size);
	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
			device);
	boost::archive::binary_iarchive ia(s);
	ia >> obj;
	return obj;
}

int main(int argc, char* argv[])
{
	//Create a driver.
	Client driver(argc, argv);
	//Get commands from server in run function
	driver.run();
	return 0;
}
