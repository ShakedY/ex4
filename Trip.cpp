

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
	list<const Passenger*>::const_iterator it = passengers.begin(), end = passengers.end();
	double satis = 0.0;
	for(;it!=end;++it)
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
void Trip::movedPoint(unsigned int distance)
{
	this->meters += distance;
}
bool Trip::isTripTaken() const
{
	return isTaken;
}
void Trip::setIsTaken()
{
	isTaken = true;
}
int Trip::getStartingTime() {
	return startingTime;
}
