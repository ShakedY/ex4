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

class RemoteDriver: public Driver
{
private:
	Socket *soc;
	template<class T> string serializeObj(T* obj);
	template<class T> T* deSerializeObj(const char* serial_str, int size);
public:
	RemoteDriver() :
			soc(NULL)
	{
	}
	;
	RemoteDriver(const BFSPoint* loc, char stat, int id, int age,
			int yearsOfExperience, Map *m, Socket *socket);
	RemoteDriver(Driver *drv, Socket *socket);
	virtual ~RemoteDriver()
	{
		delete soc;
		// TODO make sure that ~Driver also is called
	}
	virtual void setCab(Cab* cab);
	virtual void setTrip(Trip* trip);
	virtual void stopWorking();
	//Driver moves one step in it's Trip.
	virtual void moveOneStep();
};

#endif /* REMOTEDRIVER_H_ */
