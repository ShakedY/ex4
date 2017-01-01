/*
 * CabFactory.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "CabFactory.h"

CabFactory::CabFactory() {
	// TODO Auto-generated constructor stub
}

Cab* CabFactory::generateCab(int id, Cab::CabType cabType, Cab::cabColor color, Cab::Manufacturer man) {
	Cab* newCab = NULL;
	//Use the cabType enum to identify which cab to create.
	if (cabType == Cab::LUXURY)
	{
		newCab = new LuxuryCab(id, color, man);
	}
	else if (cabType == Cab::STANDARD)
	{
		newCab = new StandardCab(id, color, man);

	}
	return newCab;
}

