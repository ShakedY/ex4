#ifndef CLIENT_INPUT_H_
#define CLIENT_INPUT_H_

#include "../map/Map.h"
#include <list>
#include "../cabs/Cab.h"
#include "../drivers/Driver.h"
#include <string>

/*
 * The ClientInput will hold a struct that will define the input that the program
 * expects from the user when scanning information about the driver.
 */
class ClientInput {

public:
	//Struct which will have all the information about the driver that we will scan.
	typedef struct DriverInfo{
		int id, cabId, age, yearsOfExperience;
		char stat;
	} DriverInfo;
	//Only member will be our struct and command line arguments(in case we will need them).
	DriverInfo driverInfo;
	int argc;
	char** argv;
	
	//Constructor of this class which will get the command line arguments.
	ClientInput(int argc, char* argv[]);
	//Destructor of this class.
	virtual ~ClientInput();

	/*
	 * This function will scan information from the user about the driver and will store
	 * all the information in the DriverInfo struct which is a member of this class.
	 */
	void getDriverInfo();
};

#endif /* CLIENT_INPUT_H_ */
