#include "Server.h"
#include <stdlib.h>
using namespace std;

Server::Server(int argc, char* argv[]) :
		factory()
{
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
	const BFSPoint* location;
	do
	{
		//cout << "Insert another option" << endl;
		scanf("%d", &answer);
		switch (answer)
		{
			case 1:
				//Get number of drivers from the user.
				getNumDrivers();
				break;
			case 2:
				//Case 2,get Trip from the console and add it to the TaxiCenter.
				info.getTripInfo();
				center->addTrip(createTrip(info.tripInfo));
				break;
			case 3:
				//Case 3,get Cab from the console and add it to the TaxiCenter.
				info.getCabInfo();
				center->addCab(createCab(info.cabInfo));
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

				break;
			default:
				// no such option
				break;
		}
	} while (answer != 7);
}

void Server::getNumDrivers()
{
	int numDrivers;
	char* buffer;
	Driver * currentDriver;
	//Scan the number of drivers from the console.
	cin >> numDrivers;
	//Set the number of drivers the TaxiCenter will hold.
	center->setNumDrivers(numDrivers);
	//Now we expect to get the drivers through the socket and send them cabs.
	while(numDrivers != 0) {
		//Get a driver from the client(assume there is a cab waiting for him).
		socket->reciveData(buffer,1024);
		//Deserialize the data.
		currentDriver = getDriverFromClient(buffer);
		center->addDriver(currentDriver);
		//Add to the driver the fitting cab from the TaxiCenter.
		center->attachCabsToDrivers();
		//Now send the cab back to the client.
		sendVehicleToClient(currentDriver->getCab());
		//Decrement in loop.
		numDrivers--;
	}

}
void Server::sendVehicleToClient(Cab* cab) {
	//Serialize the cab.
	string serial_str;
	boost::iostreams::back_insert_device<string> inserter(serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s(inserter);
	boost::archive::binary_oarchive oa(s);
	oa << cab;
	s.flush();
	//Now after serializing send the series of bytes to the client.Using socket implementation.
	socket->sendData(serial_str);
}
Driver* Server::getDriverFromClient(string serialized) {
	Driver * driver;
	//Deserialize the serialized driver that was sent from the client.
	boost::iostreams::basic_array_source<char> device(serialized.c_str(),serialized.size());
	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
	boost::archive::binary_iarchive ia(s2);
	ia >> driver;
	//Return the deserialized driver.
	return driver;
}
int main(int argc, char* argv[])
{
	MainFlowAnalizer flow(argc, argv);
	return 0;
}
