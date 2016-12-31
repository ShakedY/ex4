/*
 * CabFactory.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_CABFACTORY_H_
#define SRC_CABFACTORY_H_
#include "StandardCab.h"
#include "LuxuryCab.h"


// TODO consider deleting the class
class CabFactory {
// TODO consider CabFactory have a map with symbols as keys and Cab details as value
public:
	// TODO consider an macro that will replace all "generateCab(Type)" with "generateTypeCab()"
	Cab* generateCab(int id, Cab::CabType cabType, Cab::cabColor color, Cab::Manufacturer man);
	CabFactory();
	virtual ~CabFactory(){};
};

#endif /* SRC_CABFACTORY_H_ */
