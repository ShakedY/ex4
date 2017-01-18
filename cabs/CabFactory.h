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
/*
 * This class will implement the Factory design pattern by creating a specific
 * cab based on the input it will get from it's user.
 */
class CabFactory {
// TODO consider CabFactory have a map with symbols as keys and Cab details as value
public:
	// TODO consider an macro that will replace all "generateCab(Type)" with "generateTypeCab()"
	/*
	 * This function will create a cab by getting all the required inputs to the Cab's
	 * constructor and create the correct cab according to the CabType that was entered.
	 */
	Cab* generateCab(int id, Cab::CabType cabType, Cab::cabColor color, Cab::Manufacturer man);
	//Default constructor of this class.
	CabFactory();
	//Default destructor of this class.
	virtual ~CabFactory(){};
};

#endif /* SRC_CABFACTORY_H_ */
