/*
 * RemoteDriver.h
 *
 *  Created on: Dec 30, 2016
 *      Author: adi-peled
 */

#ifndef REMOTEDRIVER_H_
#define REMOTEDRIVER_H_

#include "Driver.h"
#include "sockets/Socket.h"
#include "Client.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

/*
 * The RemoteDriver class will be derived from the Driver class,we will use it to implement
 * the communication between the Server and the Client,the RemoteDriver will be the driver that
 * the server will use,each time the Server will add a cab or a trip to the driver it will add
 * it to the RemoteDriver which will send it to Client through the socket.
 */
class RemoteDriver: public Driver
{
private:
	//Socket we will use for the communication.
	Socket *soc;
	/*
	 * This function will use a template to define a generic object that this function will get
	 * and  will return a serialize object of this class,we want this method to be private
	 * because we don't wan't anyone to serialize objects from the outside.
	 */
	template<class T> string serializeObj(T* obj);

	/*
	 * This function will use a template to define a generic object,the function will get
	 * a char array and it's size and deserialize it and return a pointer to the generic
	 * type we defined with the template.We want this function to be private so no one will
	 * deserialize objects from the outside.
	 */
	template<class T> T* deSerializeObj(const char* serial_str, int size);
public:
	//Default constructor of this class.
	RemoteDriver() :
			soc(NULL)
	{
	};

	/*
	 * Constructor for this class which will get same parameters as the one of the driver
	 * and will create a driver with them and a socket which this class will use in the
	 * communication process.
	 */
	RemoteDriver(const BFSPoint* loc, char stat, int id, int age,
			int yearsOfExperience, Map *m, Socket *socket);

	/*
	 * Constructor of this class which will the driver and a socket which we will use.
	 */
	RemoteDriver(Driver *drv, Socket *socket);

	///Default destructor of this class.
	virtual ~RemoteDriver()
	{
		//Close the socket and delete it.
		delete soc;
		// TODO make sure that ~Driver also is called
	}

	/*
	 * This method will be overriding the one that is in the Driver,when a cab will be entered
	 * we will set it to be this RemoteDriver's cab and serialize it and send it to the client.
	 */
	virtual void setCab(Cab* cab);

	/*
	 * This method will override the one that is in the Driver,when a Trip is set we will also
	 * serialize it and send it to the client.
	 */
	virtual void setTrip(Trip* trip);

	/*
	 * In this case we will override this method from the driver and also send the
	 * client a shutDown action which we defined in the Actions enum to tell it to close
	 * it's socket and stop running.
	 */
	virtual void stopWorking();

	/*
	 * This function will override the one that is in the Driver,we will moveOneStep but
	 * in addition send to the client to moveOneStep as well.
	 */
	virtual void moveOneStep();
};

#endif /* REMOTEDRIVER_H_ */
