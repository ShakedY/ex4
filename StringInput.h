/*
 * InputAnalizer.h
 *
 *  Created on: Dec 12, 2016
 *      Author: assaf
 */

#ifndef SRC_STRINGINPUT_H_
#define SRC_STRINGINPUT_H_
//#include "MainFlowAnalizer.h"
#include "Map.h"
#include <list>
#include "Cab.h"
#include "Driver.h"
#include <string>

class StringInput {
//private:
//	int getNumber(std::string info);
//	double getDoubleNumber(std::string info);
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
	mapInfo gridInfo;
	DriverInfo driverInfo;
	CabInfo cabInfo;
	TripInfo tripInfo;
	int argc;
	char** argv;
	StringInput(int argc, char* argv[]);
	virtual ~StringInput();

	void readMapInfo();
	void getDriverInfo();
	void getCabInfo();
	void getTripInfo();
};

#endif /* SRC_STRINGINPUT_H_ */
