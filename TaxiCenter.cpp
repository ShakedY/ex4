#include "TaxiCenter.h"
#include <list>
#include "RemoteDriver.h"
using namespace std;

TaxiCenter::~TaxiCenter()
{
	list<Cab*>::iterator it_cabs = cabs.begin(), end_cabs = cabs.end();
	list<Driver*>::iterator it_drivers = drivers.begin(), end_drivers =
			drivers.end();
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
	driv->setMap(this->map);
}

void TaxiCenter::addCab(Cab* cab)
{
	cabs.push_back(cab);
}

void TaxiCenter::addTrip(Trip* trip)
{
	trip->setRoad(map);
	trips.push_back(trip);
}

void TaxiCenter::addDrivers(list<Driver*> drivs)
{
	for (std::list<Driver*>::iterator it = drivs.begin(); it != drivs.end();
			++it)
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
		if (driver->isAvailable() && driver->hasCab()
				&& (d = driver->getDistanceFromSource()) < min_distance)
		{
			closest = driver;
			min_distance = d;
		}
	}
	trip = new Trip(rand(), 0, source, destination, 49.99, 0); // only 49.99! sale!!
	trip->setRoad(map);
	trips.push_front(trip);
	closest->setTrip(trip);
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
		if (driver->isAvailable() && driver->hasCab()
				&& (d = driver->getDistanceFromSource()) < min_distance)
		{
			closest = driver;
			min_distance = d;
		}
	}
	// only 49.99! sale!!
	trip = new Trip(rand(), 0, source, passenger->getDestination(), 49.99, 0);
	trip->setRoad(map);
	trip->addPassenger(passenger);
	trips.push_front(trip);		//TODO push it according to start time
	closest->setTrip(trip);
	trip->addPassenger(passenger);
}

const Point* TaxiCenter::getDriverLocation(int driverId) const
{
	const Point *loc = NULL;
	for (std::list<Driver*>::const_iterator it = drivers.begin(); it != drivers.end();
			++it)
	{
		if ((*it)->getId() == driverId)
		{
			loc = (*it)->getLocation();
			break;
		}
	}
	return loc;
}

void TaxiCenter::attachMaptoDrivers(Map* map)
{
	for (std::list<Driver*>::iterator it = drivers.begin(); it != drivers.end();
			++it)
	{
		(*it)->setMap(map);
	}
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
				(*it)->setCab((*itCabs));
			}
		}
	}
}

void TaxiCenter::attachDriversToTrips()
{
	std::list<Driver*>::iterator it = drivers.begin(), end = drivers.end();
	unsigned int size = trips.size();
	Trip* currentTrip;
	while (size > 0)
	{
		currentTrip = trips.front();
		if (currentTrip->getStartingTime() > time)
		{
			// If we didn't got to trips starting time, because the trips are sorted according
			// to the start time we can stop the loop.
			break;
		}
		for (; it != end; ++it)
		{
			if ((*it)->hasCab() && (*it)->isAvailable())
			{
				// If there is a driver with a cab and no trip assign the trip.
				(*it)->setTrip(currentTrip);
				trips.pop_front();
				size--;
				// the trip was assigned, we need to break the loop.
				break;
			}
		}
	}
}

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

//void TaxiCenter::setNumDrivers(int num) {
//	//Set fixed list size with num.
//	const size_t listSize(num);
//	list<Driver*> driversList(listSize);
//	//Set our drivers list to be of this specific size.
//	drivers = driversList;
//}

int TaxiCenter::getCurrentTime()
{
	return time;
}

void TaxiCenter::moveAllOneStep()
{
	list<Driver*>::iterator it = drivers.begin(), end = drivers.end();
	for (; it != end; ++it)
	{
		(*it)->moveOneStep();
//		if (!(*it)->moveOneStep(time))
//		{
//			cout << "End of first trip" << endl;
//			//If moveOneStep returned 0 we are at the end.
//			//Check if there is an available trip in our location.
//			if (tripAtLocation((*it)->getLocation()) != NULL)
//			{
//				cout << "Found new trip" << endl;
//				//Set a new trip for this driver.
//				(*it)->setTrip(tripAtLocation((*it)->getLocation()));
//			}
//		}
	}
	++time;
	// In this case the after assigning the trips.
	attachDriversToTrips();
}

//Trip* TaxiCenter::tripAtLocation(const BFSPoint* location)
//{
//	list<Trip*>::iterator it = trips.begin(), end = trips.end();
//	for (; it != end; ++it)
//	{
//		if ((*it)->getStart() == location)
//		{
//			//Set trip with start location of the input location
//			return (*it);
//		}
//	}
//	//No trip beggining in this location,return NULL.
//	return NULL;
//}

list<const Driver*>* TaxiCenter::getDrivers() const
{
	list<Driver*>::const_iterator it = drivers.begin(), end = drivers.end();
	list<const Driver*>* lst = new list<const Driver*>();
	for (; it != end; ++it)
	{
		lst->push_back(*it);
	}
	return lst;
}

/*list<const Trip*>* TaxiCenter::getTrips() const
 {
 //Iterate over all of the trips in the taxicenter and return a list of them.
 list<Trip*>::const_iterator it = trips.begin(), end = trips.end();
 list<const Trip*>* lst = new list<const Trip*>();
 for (;it != end;++it) {
 lst->push_back(*it);
 }
 return lst;
 }*/
