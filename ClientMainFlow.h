#ifndef CLIENT_MAINFLOW_H_
#define CLIENT_MAINFLOW_H_

#include <string>
#include "CabFactory.h"
#include "TaxiCenter.h"
#include "ClientInput.h"
#include "Map.h"

class Map;
class CabFactory;
class TaxiCenter;
class ClientInput;

class ClientMainFlow {
public:
	ClientMainFlow(int argc, char* argv[]);
	virtual ~ClientMainFlow();
	Driver* createDriver(ClientInput::DriverInfo driverInfo);
	void mainLoop(ClientInput& info);
	void printMenu();
};

#endif /* CLIENT_MAINFLOW_H_ */
