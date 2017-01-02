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

const Point* Trip::advance(unsigned int distance)
{
	const Point* ret_val;
	try
	{
		// not general but its very dumb to use loop for 1 or 2
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
		ret_val = &(*currentPosition);
	} catch (exception& e)
	{
		// we passed the end
		ret_val = &(road.back());
	}
	return ret_val;
}

unsigned int Trip::getStartingTime()
{
	return startingTime;
}

void Trip::setRoad(Map* m)
{
	// planning the best road trip for our customers.
	m->calculateShortestPath(road, startPoint, endPoint);
	currentPosition = road.begin();
	meters = road.size();
}

void Trip::restartTrip()
{
	currentPosition = road.begin();
}
