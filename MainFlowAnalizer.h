/*
 * MainFlowAnalizer.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_MAINFLOWANALIZER_H_
#define SRC_MAINFLOWANALIZER_H_
#include <string>
#include "CabFactory.h"
#include "TaxiCenter.h"
#include "StringInput.h"
#include "Map.h"
class Map;
class CabFactory;
class TaxiCenter;
class StringInput;

class MainFlowAnalizer {
private:
	// TODO delete the input string if we can change UML
	CabFactory factory;
	//std::string input;
	//StringInput input;
	TaxiCenter* center;
	Map* map;
public:

	MainFlowAnalizer(int argc, char* argv[]);
	//MainFlowAnalizer(StringInput input):factory(),input(),center(NULL){};
	//MainFlowAnalizer(std::string in,TaxiCenter* taxiCenter):factory(),input(in),center(taxiCenter){};
	virtual ~MainFlowAnalizer();
	void createTaxiCenter();
	Cab* createCab(StringInput::CabInfo cabsInfo);
	Driver* createDriver(StringInput::DriverInfo driverInfo);
	Trip* createTrip(StringInput::TripInfo tripInfo);
	void createMap(StringInput& info);
	TaxiCenter* getTaxiCenter();
	void mainLoop(StringInput& info);
	void printMenu();
};

#endif /* SRC_MAINFLOWANALIZER_H_ */
