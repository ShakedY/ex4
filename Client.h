#ifndef CLIENT_MAINFLOW_H_
#define CLIENT_MAINFLOW_H_

#include <string>
#include "CabFactory.h"
#include "TaxiCenter.h"
#include "Map.h"
#include "sockets/Udp.h"
#include "sockets/Socket.h"

class Map;
class CabFactory;
class TaxiCenter;
class ClientInput;

class Client
{
private:
	Socket* mySocket;
	Driver* driver;
	Cab* cab;
	Trip* trip;
public:
	typedef enum
	{
		moveOneStep = 0, setTrip = 1, endedTrip = 2, shutDown = 3
	} Actions;
	Client(int argc, char* argv[]);
	virtual ~Client();
	void buildDriver();
	void printMenu();
	void work();
	void getTripFromServer();
//	void moveInTrip();
	void waitForTrip();
	void run();

	template<class T>
	void serializeObj(std::string* serial_str, T* obj);
	template<class T>
	T* deSerializeObj(const char* serial_str, int size);
};

#endif /* CLIENT_MAINFLOW_H_ */
