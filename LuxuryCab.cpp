/*
 * LuxuryCab.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "LuxuryCab.h"

int LuxuryCab::getPrice() const
{
	return this->price;
}

Cab::CabType LuxuryCab::getCabType()
{
	return Cab::LUXURY;
}

