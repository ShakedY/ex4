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
		int yearsOfExperience, Map *m)
{
	status = stat;
	averageStisfaction = 0.0;
	myCab = NULL;
	currentTrip = NULL;
	location = (loc->getPoint());
	dest = NULL;
	this->id = id;
	myMap = m;
	this->yearsOfExperience = yearsOfExperience;
	this->age = age;
	isAvailableforAnotherTrip = true;
	numOfReivewsGotten = 0;
}

Driver::Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab,
		Map *m)
{
	status = stat;
	averageStisfaction = 0.0;
	myCab = cab;
	currentTrip = NULL;
	if (m != NULL)
	{
		location = (m->getTheLocation(0, 0)->getPoint());
	}
	else
	{
		location = Point(0,0);
	}
	dest = NULL;
	this->id = id;
	myMap = m;
	this->yearsOfExperience = yearsOfExperience;
	this->age = age;
	isAvailableforAnotherTrip = true;
	numOfReivewsGotten = 0;
}

bool Driver::hasCab() const
{
	return myCab != NULL;
}

bool Driver::isAvailable() const
{
	return isAvailableforAnotherTrip;
}

void Driver::setCab(Cab* cab)
{
	myCab = cab;
}

const Point* Driver::getLocation() const
{
	return &(this->location);
}

void Driver::setTrip(Trip* trip)
{
	//Delete trip we already had.
	delete currentTrip;
	//Set our trip to be the entered trip.
	currentTrip = trip;
	//Set location to beginning of trip and destination to the end of it.
	location = (currentTrip->getStart());
	dest = &(currentTrip->getEnd());
	//Restart iterator of trip.
	trip->restartTrip();
	//Set this driver to be unavailable for another trip.
	isAvailableforAnotherTrip = false;
}

const Trip* Driver::getTrip() const
{
	return currentTrip;
}

char Driver::getStatus() const
{
	return status;
}

void Driver::setMap(Map *map)
{
	// new map means starting over at (0,0)
	this->myMap = map;
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
	averageStisfaction += (rating - averageStisfaction) / numOfReivewsGotten;
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

void Driver::stopWorking()
{
	isAvailableforAnotherTrip = true;
}

Cab* Driver::getCab() const
{
	return myCab;
}

Map* Driver::getMap() const
{
	return myMap;
}

void Driver::moveOneStep()
{
	// if we have a job
	if (!isAvailableforAnotherTrip)
	{
		this->location = *(this->currentTrip->advance(myCab->getMovmentAbility()));
		isAvailableforAnotherTrip = *dest == location;
	}
}
