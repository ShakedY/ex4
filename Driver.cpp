/*
 * Driver.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author:
 */

#include "Driver.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;

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
	if (m != NULL)
	{
		location = m->getTheLocation(0, 0);
	}
	else
	{
		location = NULL;
	}
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

void Driver::setCab(Cab* cab)
{
	myCab = cab;
}

const BFSPoint* Driver::getLocation() const
{
	return this->location;
}

void Driver::setTrip(Trip* trip)
{
	currentTrip = trip;
	isDriverDriving = true;
}

const Trip* Driver::getTrip() const
{
	return currentTrip;
}

void Driver::setMap(Map *map)
{
	// new map means starting over at (0,0)
	this->myMap = map;
	this->location = map->getTheLocation(Point(0,0));
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
//	const BFSPoint *loc = myMap->getTheLocation(currentTrip->getEnd());
	isDriverDriving = true;
//	location = loc;
}

void Driver::stopWorking()
{
	isDriverDriving = false;
	currentTrip = NULL;
}

Cab* Driver::getCab() const
{
	return myCab;
}

Trip* Driver::getTrip()
{
	return currentTrip;
}

void Driver::moveOneStep(unsigned int time)
{
	unsigned int movment;
	// First we will check if the time is past the Trip's starting time.
	if (currentTrip->getStartingTime() >= time)
	{
		//We are past the starting time so moveOneStep.
		movment = myCab->getMovmentAbility();
		this->location = this->currentTrip->advence(movment);
	}
}
