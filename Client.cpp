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
#define BUFFSIZE 1024

using namespace std;
using namespace boost::archive;

Client::Client(int argc, char* argv[])
{
	//Choose socket to run on port 110000, enter false
	// because it's not a server, no need to bind.
	mySocket = new Udp(0, 8000);
	driver = NULL;
	cab = NULL;
	trip = NULL;
	mySocket->initialize();
	buildDriver();
}

Client::~Client()
{
	delete driver;
	delete cab;
	const list<const BFSPoint*>& road = trip->getRoad();
	list<const BFSPoint*>::const_iterator it = road.begin(), end = road.end();
	while (it != end)
	{
		// same as:
		// delete *it_cabs;
		// it_cabs++;
		delete *it++;
	}
	delete trip;
	//Call socket's destructor to close it.
	delete mySocket;
}

void Client::buildDriver()
{
	string serial_str;
	int id, cabId, age, yearsOfExperience, bytes;
	char stat;
	char buffer[BUFFSIZE];
	
	//-------------------------get driver's members as input---------------
	scanf("%d,%d,%c,%d,%d", &id, &age, &stat, &yearsOfExperience, &cabId);
	driver = new Driver(id, age, stat, yearsOfExperience, NULL, NULL);

	//---------------------------serializing the driver--------------------
	this->serializeObj<Driver>(&serial_str, driver);

	// Send serialized string through the socket.
	cout <<"Sending" << endl;
	mySocket->sendData(serial_str);

	// Now the client will wait to receive the cab from the server.
	bytes = mySocket->reciveData(buffer, BUFFSIZE);
	cab = deSerializeObj<Cab>(buffer, bytes - 1);
	driver->setCab(cab);

	// Now the client will wait to receive the trip from the server.
	bytes = mySocket->reciveData(buffer, BUFFSIZE);
	trip = deSerializeObj<Trip>(buffer, bytes - 1);
	driver->setTrip(trip);
	cout << "Got my trip" << endl;
	cout <<"Start point: " << trip->getStart() << "  end Point: " << trip->getEnd() << endl;
}

void Client::printMenu()
{
	cout << "Insert driver (id,age,status,experience,vehicle_id) " << endl;
}

void Client::work()
{
	const BFSPoint *end = trip->getRoadEnd();
	char action, buff[BUFFSIZE];
	unsigned int time;
	do
	{
		// TODO check possible problems of reading 1 byte(it might write 2 because of the \0)
		mySocket->reciveData(&action, 1);
		if (action == (char)moveOneStep)
		{
			mySocket->reciveData(buff, 21);
			time = atoi(buff);
			driver->moveOneStep(time);
		}
	} while(action != (char)shutDown && end != driver->location);
	// TODO replace this ugly shit. It's here to prevent the server from
	// sending to a socket
	if (action != (char)shutDown)
	{
		do
		{
			// TODO check possible problems of reading 1 byte(it might write 2 because of the \0)
			mySocket->reciveData(&action, 1);
		} while(action != (char)shutDown);
	}
}

template<class T>
void Client::serializeObj(std::string* serial_str, T* obj)
{
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
	boost::iostreams::basic_array_source<char> device(serial_str, size);
	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
			device);
	boost::archive::binary_iarchive ia(s);
	ia >> obj;
	return obj;
}

int main(int argc, char* argv[])
{
	Client driver(argc, argv);
	driver.work();
	return 0;
}
