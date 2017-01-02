

#include "MainFlowAnalizer.h"
#include <stdlib.h>
using namespace std;

MainFlowAnalizer::MainFlowAnalizer(int argc, char* argv[]) :
		factory()
{
	StringInput input(argc, argv);
	input.readMapInfo();
	createMap(input);
	mainLoop(input);
}

MainFlowAnalizer::~MainFlowAnalizer()
{
	delete center;
	delete map;
}

void MainFlowAnalizer::createTaxiCenter()
{
	center = new TaxiCenter(map);
}

Cab* MainFlowAnalizer::createCab(StringInput::CabInfo cabsInfo)
{
	return factory.generateCab(cabsInfo.id, cabsInfo.taxi_type, cabsInfo.color,
			cabsInfo.manufacturer);
}

Driver* MainFlowAnalizer::createDriver(StringInput::DriverInfo driverInfo)
{
	Cab* cab = center->getCab(driverInfo.cabId);
	return new Driver(driverInfo.id, driverInfo.age, driverInfo.stat,
			driverInfo.yearsOfExperience, cab, map);
}

Trip* MainFlowAnalizer::createTrip(StringInput::TripInfo tripInfo)
{
	Point start(tripInfo.x_start, tripInfo.y_start), end(tripInfo.x_end,
			tripInfo.y_end);
	return new Trip(tripInfo.id, tripInfo.num_passengers, start, end,
			tripInfo.tariff);
}

void MainFlowAnalizer::createMap(StringInput& info)
{
	map = new Map(info.gridInfo.width, info.gridInfo.height,
			*(info.gridInfo.obstacles));
}

TaxiCenter* MainFlowAnalizer::getTaxiCenter()
{
	return center;
}

void MainFlowAnalizer::mainLoop(StringInput& info)
{
	center = new TaxiCenter(map);
	//printMenu();
	int answer, driver_id;
	const Point* location;
	do
	{
		//cout << "Insert another option" << endl;
		scanf("%d", &answer);
		switch (answer)
		{
			case 1:
				info.getDriverInfo();
				center->addDriver(createDriver(info.driverInfo));
				break;
			case 2:
				info.getTripInfo();
				center->addTrip(createTrip(info.tripInfo));
				break;
			case 3:
				info.getCabInfo();
				center->addCab(createCab(info.cabInfo));
				break;
			case 4:
				//cout << "Insert driver id" << endl;
				scanf("%d", &driver_id);
				location = (*center).getDriverLocation(driver_id);

				if (location != NULL)
					cout << location << endl;
				else
					cout << "No driver with this id" << endl;
				break;
			case 6:
				center->attachCabsToDrivers();
				center->attachDriversToTrips();
//				(*center).startWorking();
				center->endWorking();
				break;
//			case 7:
//				break;
			default:
				// no such option
				break;
		}
	} while (answer != 7);
}

void MainFlowAnalizer::printMenu()
{
	cout << "1. Insert driver (id,age,status,experience,vehicle_id) " << endl;
	cout
			<< "2. Insert new drive (id,x_start,y_start,x_end,y_end,num_passengers,tariff) "
			<< endl;
	cout
			<< "3. Insert a vehicle (id,taxi_type,manufacturer,color) - (int,{1: Normal Cab,2: Luxury Cab},char:{H,S,T,F},char:{R,B,G,P,W}) "
			<< endl;
	cout << "4. Request driver location (driver_id) " << endl;
	cout << "6. Start driving " << endl;
	cout << "7. Exit program " << endl;
}

int main1(int argc, char* argv[])
{
	MainFlowAnalizer flow(argc, argv);
	return 0;
}
