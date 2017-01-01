#ifndef CLIENT_INPUT_H_
#define CLIENT_INPUT_H_

#include "Map.h"
#include <list>
#include "Cab.h"
#include "Driver.h"
#include <string>


class ClientInput {

public:
	typedef struct DriverInfo{
		int id, cabId, age, yearsOfExperience;
		char stat;
	} DriverInfo;

	DriverInfo driverInfo;
	int argc;
	char** argv;
	
	ClientInput(int argc, char* argv[]);
	virtual ~ClientInput();

	void getDriverInfo();
};

#endif /* CLIENT_INPUT_H_ */
