/*
 * Server.h
 *
 *  Created on: Dec 25, 2016
 *      Author: lior
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <string>
#include "StringInput.h"
#include "sockets/Tcp.h"
#include "CabFactory.h"
#include "Driver.h"
#include "RemoteDriver.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <pthread.h>
//Forward declaration of StringInput
class StringInput;

/*
 * The Server class will communicate with the user through the console,it will
 * hold the TaxiCenter which will manage all the connections between drivers,cabs
 * and trips and communicate with the clients as well.
 */
class Server {
private:
	CabFactory factory;
	//Socket which we will use to interact with the client.
	Socket* socket;
	TaxiCenter* center;
	Map* map;
public:
	struct Param{
		Socket* serverSocket;
		pthread_mutex_t locker;
	};
	Server();
	Server(int argc,char* argv[]);
	virtual ~Server();
	/*
	 * This function will create a cab for the driver, after
	 * the driver will be sent from the client.
	 */
	Cab* createCab(StringInput::CabInfo info);
	/*
	 * This function will create a Trip which we will send
	 * to the client after serializing it.
	 */
	Trip* createTrip(StringInput::TripInfo info);
	/*
	 * Creates map which will be stored by the server and used to calculate
	 * the trips.
	 */
	void createMap(StringInput& info);
	/*
	 * Main loop which will run the interation with the user through the
	 * console,based on the input this function will run the fitting operation.
	 */
	void mainLoop(StringInput& info);
	/*
	 * This function will get a driver from the client.
	 * It will get in it's input the serialized driver.
	 * In response to getting a driver the server will create a
	 * vehicle and send it to the client.This function will deserialize
	 * the output.
	 */
	Driver* getDriverFromClient();
	/*
	 * Get the number of drivers from the user and create the correct list accordingly
	 */
	void getNumDrivers();
	/*
	 * After getting a driver from the client we want to send
	 * a serialized cab back to the client.
	 */
	void sendVehicleToClients();
	//Send a Trip to the Driver
	void sendTrip();
	template<class T>
	/*
	 * General function to serialize and deserialize an object,
	 * we will use a template so that we could use these functions
	 * to serialize and deserialize plenty of objects cause the code
	 * is the same for all of them.
	 */
	static void serializeObj(std::string* serial_str, T* obj);
	template<class T>
	static T* deSerializeObj(const char* serial_str, int size);
	/*
	 * Static method which we will run in seperate threads to create
	 * connections with multiple clients at once because accept method of
	 * Tcp is code blocking.It will get a mutex lock which we
	 * will use as a parameter and when it will connect with the client it will
	 *  create the RemoteDriver and add it carefully to the TaxiCenter via the Server
	 *  by using the lock. After the run of the accept the main thread will know to
	 *  continue because we have a counter that will indicate it for him and this
	 *  function will continue managing it's specific client in it's own thread and
	 *  the main thread will be able to comunicate with the other threads by updating
	 *  a global data structure.
	 */
	static void* manageClient(void* param);
	static void waitForTrip(Driver* driver);
};

#endif /* SERVER_H_ */
