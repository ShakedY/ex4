/*
 * StandardCab.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "StandardCab.h"

int StandardCab::getPrice() const
{
	return this->price;
}

Cab::CabType StandardCab::getCabType()
{
	return Cab::STANDARD;
}
