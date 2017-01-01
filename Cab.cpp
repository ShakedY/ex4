/*
 * Cab.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "Cab.h"

int Cab::getCabId() const
{
	return id;
}

char Cab::getManufacturer() const
{
	return manufacturer;
}

int Cab::getKilometerage() const
{
	return numOfKilometers;
}

char Cab::getColor() const
{
	return color;
}

BFSPoint* Cab::getLocation() const
{
	return location;
}

unsigned int Cab::getMovmentAbility()
{
	return movmentAbility;
}

void Cab::setLocation(const BFSPoint* point)
{
	delete location;
	location = new BFSPoint(point->getX(), point->getY());
}
template<class Archive>
void Cab::serialize(Archive & ar,const unsigned int version) {
	ar & id;
	ar & numOfKilometers;
	ar & tariff;
	ar & color;
	ar & location;
	ar & manufacturer;
}
