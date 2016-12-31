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

unsigned int Cab::getMovmentAbility()
{
	return movmentAbility;
}

