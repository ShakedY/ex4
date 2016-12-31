#include "Trip.h"
using namespace std;

void Trip::addPassenger(const Passenger *passenger)
{
	this->passengers.push_back(passenger);
	++numOfPassengers;
}

void Trip::addPassengers(list<const Passenger*> passengers)
{
	numOfPassengers += passengers.size();
	this->passengers.merge(passengers);
}

double Trip::getPassengersSatisfaction() const
{
	list<const Passenger*>::const_iterator it = passengers.begin(), end =
			passengers.end();
	double satis = 0.0;
	for (; it != end; ++it)
	{
		satis += (*it)->produceTripReview();
	}
	return satis / numOfPassengers;
}

int Trip::getId() const
{
	return this->rideId;
}

int Trip::getMeters() const
{
	return meters;
}

const Point& Trip::getStart() const
{
	return startPoint;
}

const Point& Trip::getEnd() const
{
	return endPoint;
}

int Trip::getNumOfPassengers() const
{
	return this->numOfPassengers;
}

int Trip::getTariff() const
{
	return this->tariff;
}

const BFSPoint* Trip::advence(unsigned int distance)
{
	const BFSPoint* ret_val;
	this->meters += distance;
	try
	{
		// not general but its very dumb to you loop for 1 or 2
		switch(distance)
		{
			case 2:
				++currentPosition;
			case 1:
				++currentPosition;
				break;
			default:
				break;
		}
		ret_val = *currentPosition;
	} catch (exception& e)
	{
		ret_val = road.back();
	}
	return ret_val;
}

bool Trip::isTripTaken() const
{
	return isTaken;
}

void Trip::setIsTaken()
{
	isTaken = true;
}

unsigned int Trip::getStartingTime()
{
	return startingTime;
}

void Trip::setRoad(Map* m)
{
	// planning the best road trip for our customers.
	const BFSPoint* st = m->getTheLocation(startPoint), *end =
			m->getTheLocation(endPoint);
	m->calculateShortestPath(road, *st, *end);
	currentPosition = road.begin();
}

const BFSPoint* Trip::getRoadStart() const
{
	return road.front();
}

const BFSPoint* Trip::getRoadEnd() const
{
	return road.back();
}

const std::list<const BFSPoint*>& Trip::getRoad()
{
	return road;
}
