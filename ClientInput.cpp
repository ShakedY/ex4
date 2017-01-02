#include "ClientInput.h"

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "BFSPoint.h"
#define IS_DIGIT(character) ((character >= '0') && (character <= '9'))
#define IS_MARITAL_

using namespace::std;

ClientInput::ClientInput(int argNum, char* args[]) {
	argc = argNum;
	argv = args;
}

ClientInput::~ClientInput() {
}

void ClientInput::getDriverInfo() {
	int id, age, experience, vehicle_id;
	char status;
	
	//Scan from the user all the driver information with scanf function.
	scanf("%d,%d,%c,%d,%d", &id, &age, &status, &experience, &vehicle_id);

	//Set members of the DriverInfo struct with the information that we scanned.
	driverInfo.id = id;
	driverInfo.age = age;
	driverInfo.stat = status;
	driverInfo.yearsOfExperience = experience;
	driverInfo.cabId = vehicle_id;
}
