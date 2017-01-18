#include "Trip.h"
using namespace std;

void Trip::addPassenger(const Passenger *passenger)
{
	this->passengers.push_back(passenger);
	++numOfPassengers;
}

void Trip::addPassengers(list<const Passenger*> passengers)
{
	//Add a list of passengers to the current passengers.
	numOfPassengers += passengers.size();
	this->passengers.merge(passengers);
}

double Trip::getPassengersSatisfaction() const
{
	//Calculate randomly in a loop the satisfaction of the passengers.
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
	// not general but its very dumb to use loop for 1 or 2
	switch(distance)
	{
		case 2: {
			//Check first if we are one step away from end point.
			std::list<Point>::iterator it = currentPosition;
			if ((*(++it)) == endPoint) {
				//We are one step away from end point so move only one.
				++currentPosition;
			} else {
				//We have two or more steps to take till the end point.
				++currentPosition;
				++currentPosition;
				}
				break;
			}
			case 1:
				//Case of standard cab,move only one point.
				++currentPosition;
				break;
			default:
				break;
		}
	//Set return value to be current position in the trip.
	ret_val = &(*currentPosition);
	return ret_val;
}

unsigned int Trip::getStartingTime()
{
	return startingTime;
}

void Trip::setRoad(Map* m)
{
	// planning the best road trip for our customers.Calculate the shortest path.
	m->calculateShortestPath(road, startPoint, endPoint);
	currentPosition = road.begin();
	//Set the length of the trip in meters to size of the road.
	meters = road.size();
}

void Trip::restartTrip()
{
	currentPosition = road.begin();
}
