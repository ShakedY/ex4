#include "Server.h"
#include <stdlib.h>
#define BUFFSIZE 1024


Server::Server(int argc, char* argv[]) :
		factory(),connectedToClient(false)
{
	//Create Udp socket.
	socket = new Udp(1,8000);
	socket->initialize();
	StringInput input(argc, argv);
	input.readMapInfo();
	createMap(input);
	mainLoop(input);
}

Server::~Server()
{
	delete center;
	delete map;
}

void Server::createTaxiCenter()
{
	center = new TaxiCenter(map);
}

Cab* Server::createCab(StringInput::CabInfo cabsInfo)
{
	return factory.generateCab(cabsInfo.id, cabsInfo.taxi_type, cabsInfo.color,
			cabsInfo.manufacturer);
}

Trip* Server::createTrip(StringInput::TripInfo tripInfo)
{
	Point start(tripInfo.x_start, tripInfo.y_start), end(tripInfo.x_end,
			tripInfo.y_end);
	return new Trip(tripInfo.id, tripInfo.num_passengers, start, end,
			tripInfo.tariff,tripInfo.time);
}

void Server::createMap(StringInput& info)
{
	map = new Map(info.gridInfo.width, info.gridInfo.height,
			*(info.gridInfo.obstacles));
}

TaxiCenter* Server::getTaxiCenter()
{
	return center;
}

void Server::mainLoop(StringInput& info)
{
	center = new TaxiCenter(map);
	//printMenu();
	int answer, driver_id;
	char junk;
	const BFSPoint* location;
	do
	{
		cout << "Insert another option" << endl;
		scanf("%d", &answer);
		scanf("%c",&junk);
		switch (answer)
		{
			case 1:
				//Get number of drivers from the user.
				cout <<"Going into numDrivers function" << endl;
				getNumDrivers();
				cout <<"Ended call of function" << endl;
				break;
			case 2:
				//Case 2,get Trip from the console and add it to the TaxiCenter.
				info.getTripInfo();
				//Attach the trips to the drivers(if there are any).
				center->attachDriversToTrips();
				center->addTrip(createTrip(info.tripInfo));
				break;
			case 3:
				//Case 3,get Cab from the console and add it to the TaxiCenter.
				info.getCabInfo();
				center->addCab(createCab(info.cabInfo));
				cout <<"Added cab" << endl;
				break;
			case 4:
				//Case 4,get id of driver and print it's location.
				scanf("%d", &driver_id);
				location = center->getDriverLocation(driver_id);

				if (location != NULL)
					cout << location << endl;
				else
					cout << "No driver with this id" << endl;
				break;
			case 9:
				//In this case the after assigning the trips.
				center->moveAllOneStep();
				break;
			default:
				// no such option
				break;
		}
	} while (answer != 7);
}

void Server::getNumDrivers()
{
	cout <<"Getting number of drivers" << endl;
	int numDrivers, size;
	char buffer[BUFFSIZE];
	RemoteDriver  currentDriver;
	Driver *drv;
	//Set boolean to be true to know we already connected to the client.
	connectedToClient = true;
	/* we use list, it doesn't effects us. */
	//Scan the number of drivers from the console.
	scanf("%d",&numDrivers);
	//Now we expect to get the drivers through the socket and send them cabs.
	while(numDrivers-- != 0) {
		cout <<"Before getting driver" << endl;
		// Deserialize the data.
		size = socket->reciveData(buffer, BUFFSIZE);
		cout <<"Before deserialize" << endl;
		drv = deSerializeObj<Driver>(buffer, size);
		cout << "ID: " << drv->getId() << endl;
		cout <<"Got remote" << endl;
		currentDriver = RemoteDriver(drv, new Udp(1,8000));
		cout <<"Right after" << endl;
		//delete drv;
		cout <<"After creation" << endl;
		center->addDriver(&currentDriver);
	}
	cout <<"Here got driver" << endl;
	// Add to the driver the fitting cab from the TaxiCenter.
	cout << "Attaching cabs" << endl;
	center->attachCabsToDrivers();
	cout <<"Attaching trips" << endl;
	center->attachDriversToTrips();
	cout << "Send vehicles" << endl;
	// Now send the cab back to the client.
	sendVehicleToClients();
	cout <<"Send trips " << endl;
	//Send the trips to the clients.
	sendTrip();
	cout <<"After sending the trips" << endl;
}
void Server::sendTrip() {
	//If we are already connected to the driver,send a Trip do nothing otherwise.
	if (connectedToClient) {
	string serial_str;
	RemoteDriver* remote;
	list<const Driver*>* trips_list = center->getDrivers();
	list<const Driver*>::iterator it = trips_list->begin(),end = trips_list->end();
	for (;it != end;++it) {
		if (trips_list->size() >= 1) {
			remote = (RemoteDriver*)(*it);
			remote->setSocket(new Udp(1,8000));
			//Case of one or more trips,we have only 1 driver now so send one trip and break.
			serializeObj(&serial_str,remote->getTrip());
			socket->sendData(serial_str); //TODO adresses support when using many clients.
			break;
		}
	}
	}
}
void Server::sendVehicleToClients() {
	string serial_str;
	list<const Driver*>* employee_list = center->getDrivers();
	list<const Driver*>::iterator it = employee_list->begin(), end = employee_list->end();
	for(; it != end; ++it)
	{
		cout <<"Has: " << (*it)->hasCab() << endl;
		serializeObj(&serial_str, (*it)->getCab());
		cout <<"Sending" << endl;
		socket->sendData(serial_str); // TODO addresses support
		cout <<"After sending" << endl;
	}
}

template<class T>
void Server::serializeObj(std::string* serial_str, T* obj)
{
	cout <<"Serializng" << endl;
	boost::iostreams::back_insert_device<std::string> inserter(*serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
			inserter);
	boost::archive::binary_oarchive oa(s);
	cout <<"Before" << endl;
	oa << obj;
	cout << "After" << endl;
	s.flush();
}

template<class T>
T* Server::deSerializeObj(const char* serial_str, int size)
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
	Server flow(argc, argv);
	return 0;
}
