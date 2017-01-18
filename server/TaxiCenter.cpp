#include "TaxiCenter.h"
#include <list>
#include "../drivers/RemoteDriver.h"
using namespace std;
TaxiCenter* TaxiCenter::instance = NULL;

TaxiCenter* TaxiCenter::getInstance(Map* m)
{
	if (!instance)
	{
		//Case where instance is NULL and it wasn't created yet.
		instance = new TaxiCenter(m);
	}
	return instance;
}

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
	//We wil open a thread to calculate the trip which we will join while attaching it.
	pthread_t thread;
	TripsCalcThread* calcThread = TripsCalcThread::getInstance();
	//Calculate the trip by using the thread.
	pthread_create(&thread, NULL, TaxiCenter::setRoadFromThread, trip);
	calcThread->addThread(thread, trip->getId());
	//Make sure trips are sorted by starting time.
	std::list<Trip*>::iterator it = trips.begin();
	while (it != trips.end()
			&& trip->getStartingTime() >= (*it)->getStartingTime())
	{
		++it;
	}
	trips.insert(it, trip);
}

void* TaxiCenter::setRoadFromThread(void * params)
{
	//Calculation* calc = (Calculation*) param;
	Trip* trip = (Trip*) params;
	Map* map = Map::getInstance();
	trip->setRoad(map);
	return NULL;
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
	for (std::list<Driver*>::const_iterator it = drivers.begin();
			it != drivers.end(); ++it)
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
	GlobalInfo* global = GlobalInfo::getInstance();
	std::list<Driver*>::iterator it = drivers.begin();
	//Iterate through cabs and drivers and give cabs to drivers with no cab.
	for (std::list<Cab*>::iterator itCabs = cabs.begin(); itCabs != cabs.end();
			++itCabs)
	{
		for (;
				it != drivers.end(); ++it)
		{
			if ((*it)->hasCab() == false)
			{
				global->setIthCab((*it)->getId(), (*itCabs));
				++it;
				break;
			}
		}
	}
}

void TaxiCenter::attachDriversToTrips()
{
	GlobalInfo* global = GlobalInfo::getInstance();
	std::list<Driver*>::iterator it = drivers.begin(), end = drivers.end();
	TripsCalcThread* calcThread = TripsCalcThread::getInstance();
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
		for (it = drivers.begin(); it != end; ++it)
		{
			if ((*it)->hasCab() && (*it)->isAvailable())
			{
				//Before setting the trip make sure the thread ends by calling join.
				pthread_join(calcThread->getThreadOfTrip(currentTrip->getId()),
						NULL);
				// If there is a driver with a cab and no trip assign the trip.
				(*it)->setAvailable(false);
				global->setIthTrip((*it)->getId(), currentTrip);
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
	GlobalInfo* global = GlobalInfo::getInstance();
	global->endThreads();
	//Iterate through all the drivers and tell them to stop working.
	for (std::list<Driver*>::iterator itDrivers = drivers.begin();
			itDrivers != drivers.end(); ++itDrivers)
	{
		if ((*itDrivers)->getTrip() != NULL && (*itDrivers)->hasCab() == true)
		{
			(*itDrivers)->stopWorking();
		}
	}
}

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
	}
	++time;
	// In this case the after assigning the trips.
	attachDriversToTrips();
}

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
