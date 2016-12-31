/*
 * Driver.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "Driver.h"
using namespace std;

Driver::Driver(const BFSPoint* loc, char stat, int id, int age,
		int yearsOfExperience, Map *m) :
		passengers()
{
	status = stat;
	averageStisfaction = 0.0;
	myCab = NULL;
	currentTrip = NULL;
	location = loc;
	this->id = id;
	myMap = m;
	this->yearsOfExperience = yearsOfExperience;
	this->age = age;
	isDriverDriving = false;
	numOfReivewsGotten = 0;
}

Driver::Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab,
		Map *m) :
		passengers()
{
	status = stat;
	averageStisfaction = 0.0;
	myCab = cab;
	currentTrip = NULL;
	location = m->getTheLocation(0, 0);
	this->id = id;
	myMap = m;
	this->yearsOfExperience = yearsOfExperience;
	this->age = age;
	isDriverDriving = false;
	numOfReivewsGotten = 0;
}
bool Driver::hasCab() const
{
	return myCab != NULL;
}
bool Driver::isDriving() const
{
	return isDriverDriving;
}
void Driver::assignCab(Cab* cab)
{
	myCab = cab;
}
const BFSPoint* Driver::getLocation() const
{
	return myCab->getLocation();
}
void Driver::setTrip(Trip* trip)
{
	currentTrip = trip;
	startDriving();
}
const Trip* Driver::getTrip() const
{
	return currentTrip;
}
void Driver::setMap(Map *map)
{
	this->myMap = map;
}
void Driver::addPassenger(const Passenger *passenger)
{
	this->passengers.push_back(passenger);
}
void Driver::removePassenger(const Passenger *passenger)
{
	this->passengers.remove(passenger);
}
void Driver::addReview(double rating)
{
//	new rating =
//
//	(averageStisfaction * numOfReivewsGotten + rating) / (numOfReivewsGotten + 1)
//
//	(averageStisfaction * numOfReivewsGotten + averageStisfaction
//			- averageStisfaction + rating) / (numOfReivewsGotten + 1)
//
//	averageStisfaction + (rating - averageStisfaction) / (numOfReivewsGotten + 1)
	++numOfReivewsGotten;
	this->averageStisfaction += (rating - averageStisfaction)
			/ numOfReivewsGotten;
}
double Driver::getAvgSatisfaction() const
{
	return averageStisfaction;
}
int Driver::getId() const
{
	return id;
}
int Driver::getAge() const
{
	return age;
}
int Driver::getExperience() const
{
	return yearsOfExperience;
}
void Driver::setExperience(int years)
{
	this->yearsOfExperience = years;
}

void Driver::startDriving()
{
	const BFSPoint *loc = myMap->getTheLocation(currentTrip->getEnd());
	isDriverDriving = true;
	myCab->setLocation(loc);
	location = loc;
}

void Driver::stopWorking()
{
	isDriverDriving = false;
	currentTrip = NULL;
}

