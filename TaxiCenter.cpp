
#include "TaxiCenter.h"
#include <list>
using namespace std;

TaxiCenter::~TaxiCenter()
{
	list<Cab*>::iterator it_cabs = cabs.begin(), end_cabs = cabs.end();
	list<Driver*>::iterator it_drivers = drivers.begin(), end_drivers = drivers.end();
	list<Trip*>::iterator it_trips = trips.begin(), end_trips = trips.end();
	while (it_cabs != end_cabs)
	{
		// same as:
		// delete *it_cabs;
		// it_cabs++;
		delete *it_cabs++;
	}
	while (it_drivers != end_drivers)
	{
		// same as:
		// delete *it_drivers;
		// it_drivers++;
		delete *it_drivers++;
	}
	while (it_trips != end_trips)
	{
		// same as:
		// delete *it_trips;
		// it_trips++;
		delete *it_trips++;
	}
}

void TaxiCenter::addDriver(Driver* driv)
{
	drivers.push_back(driv);
}

void TaxiCenter::addCab(Cab* cab)
{
	cabs.push_back(cab);
}

void TaxiCenter::addTrip(Trip* trip)
{
	trips.push_back(trip);
}

void TaxiCenter::addDrivers(list<Driver*> drivs)
{
	for (std::list<Driver*>::iterator it = drivs.begin(); it != drivs.end(); ++it)
	{
		addDriver(*it);
	}
}

void TaxiCenter::addCabs(list<Cab*> cabs)
{
	for (std::list<Cab*>::iterator it = cabs.begin(); it != cabs.end(); ++it)
	{
		addCab(*it);
	}
}

void TaxiCenter::sendTaxi(const BFSPoint* source, const BFSPoint* destination)
{
	unsigned d, min_distance = (unsigned) -1;
	Trip *trip;
	Driver *closest, *driver;
	map->giveToAllMapUsersTheirDistanceFrom(source->getX(), source->getY());
	list<Driver*>::iterator it = drivers.begin(), end = drivers.end();
	for (; it != end; ++it)
	{
		driver = *it;
		if (driver->isDriving() == false && driver->hasCab()
				&& (d = driver->getDistanceFromSource()) < min_distance)
		{
			closest = driver;
			min_distance = d;
		}
	}
	trip = map->calcTrip(*source, *destination);
	trips.push_front(trip);
	closest->setTrip(trip);
	trip->setIsTaken();
}

const BFSPoint* TaxiCenter::getDriverLocation(int driverId)
{
	for (std::list<Driver*>::iterator it = drivers.begin(); it != drivers.end();
			++it)
		if ((*it)->getId() == driverId)
			return (*it)->getLocation();
	return NULL;
}

void TaxiCenter::attachMaptoDrivers(Map* map)
{
	for (std::list<Driver*>::iterator it = drivers.begin();
			it != drivers.end(); ++it)
	{
		(*it)->setMap(map);
	}
}

void TaxiCenter::sendTaxi(Passenger* passenger)
{
	Trip *trip;
	const BFSPoint *source = passenger->getSource();
	unsigned d, min_distance = (unsigned) -1;
	Driver *closest, *driver;
	map->giveToAllMapUsersTheirDistanceFrom(source->getX(), source->getY());
	list<Driver*>::iterator it = drivers.begin(), end = drivers.end();
	for (; it != end; ++it)
	{
		driver = *it;
		if (driver->isDriving() == false && driver->hasCab()
				&& (d = driver->getDistanceFromSource()) < min_distance)
		{
			closest = driver;
			min_distance = d;
		}
	}
	closest->addPassenger(passenger);
	trip = map->calcTrip(*source, *(passenger->getDestination()));
	trips.push_front(trip);
	closest->setTrip(trip);
	trip->addPassenger(passenger);
	trip->setIsTaken();
}

//bool TaxiCenter::checkingIfDriving(Driver* driver)
//{
//	return true;
//}

std::list<Driver*> TaxiCenter::getDriversList() const
{
	return drivers;
}

std::list<Cab*> TaxiCenter::getCabsList() const
{
	return cabs;
}

Cab* TaxiCenter::getCab(int cabId) const
{
	Cab *taxi = NULL;
	list<Cab*>::const_iterator it = cabs.begin();
	for (; it != cabs.end(); ++it)
	{
		if ((*it)->getCabId() == cabId)
		{
			taxi = *it;
			break;
		}
	}
	return taxi;
}

void TaxiCenter::attachCabsToDrivers()
{
	for (std::list<Cab*>::iterator itCabs = cabs.begin(); itCabs != cabs.end();
			++itCabs)
	{
		for (std::list<Driver*>::iterator it = drivers.begin();
				it != drivers.end(); ++it)
		{
			if ((*it)->hasCab() == false)
			{
				(*it)->assignCab((*itCabs));
			}
		}
	}
}

void TaxiCenter::attachDriversToTrips()
{
	for (std::list<Trip*>::iterator it = trips.begin(); it != trips.end(); ++it)
	{
		if ((*it)->isTripTaken() == false)
		{
			for (std::list<Driver*>::iterator itDrivers = drivers.begin();
					itDrivers != drivers.end(); ++itDrivers)
			{
				if ((*itDrivers)->getTrip() == NULL && (*itDrivers)->hasCab())
				{
					(*it)->setIsTaken();
					(*itDrivers)->setTrip((*it));
				}
			}
		}
	}
}

//void TaxiCenter::startWorking()
//{
//	for (std::list<Driver*>::iterator itDrivers = drivers.begin();
//			itDrivers != drivers.end(); ++itDrivers)
//	{
//		if ((*itDrivers)->getTrip() != NULL && (*itDrivers)->hasCab() == true)
//		{
//			(*itDrivers)->startDriving();
//		}
//	}
//}

void TaxiCenter::endWorking()
{
	for (std::list<Driver*>::iterator itDrivers = drivers.begin();
			itDrivers != drivers.end(); ++itDrivers)
	{
		if ((*itDrivers)->getTrip() != NULL && (*itDrivers)->hasCab() == true)
		{
			(*itDrivers)->stopWorking();
		}
	}
}
void TaxiCenter::setNumDrivers(int num) {
	//Set fixed list size with num.
	const size_t listSize(num);
	list<Driver*> driversList(listSize);
	//Set our drivers list to be of this specific size.
	drivers = driversList;
}
int TaxiCenter::getCurrentTime() {
	return time;
}
