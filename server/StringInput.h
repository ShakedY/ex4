/*
 * InputAnalizer.h
 *
 *  Created on: Dec 12, 2016
 *      Author: assaf
 */

#ifndef SRC_STRINGINPUT_H_
#define SRC_STRINGINPUT_H_
//#include "MainFlowAnalizer.h"
#include "../map/Map.h"
#include <list>
#include "../cabs/Cab.h"
#include "../drivers/Driver.h"
#include <string>

/*
 * The StringInput class will hold several structs which define specific information the
 * user will enter to the console about several objects(trip,driver,cab etc)/
 */
class StringInput {
public:
	//Create structs that will define the info we will get from the user about each object.
	typedef struct mapInfo
	{
		int height;
		int width;
		std::list<Point>* obstacles;
	} mapInfo;
	typedef struct DriverInfo
	{
		int id, cabId, age, yearsOfExperience;
		char stat;
	} DriverInfo;
	typedef struct TripInfo
	{
		int id, x_start, y_start, x_end, y_end, num_passengers,time;
		double tariff;
	} TripInfo;
	typedef struct CabInfo
	{
		int id;
		Cab::CabType taxi_type;
		Cab::Manufacturer manufacturer;
		Cab::cabColor color;
	} CabInfo;
	//Use these structs as public members of this class(Server will have access to them).
	mapInfo gridInfo;
	DriverInfo driverInfo;
	CabInfo cabInfo;
	TripInfo tripInfo;
	int argc;
	char** argv;

	//Constructor of this class which will get the command line arguments.
	StringInput(int argc, char* argv[]);

	//Default destructor.
	virtual ~StringInput();

	//Get info about the map from the console.
	void readMapInfo();

	//Get info about the driver from the console.
	void getDriverInfo();

	//Get info about a cab from the console.
	void getCabInfo();

	//Get info about the Trip from the console.
	void getTripInfo();
};

#endif /* SRC_STRINGINPUT_H_ */
