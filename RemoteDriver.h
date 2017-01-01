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
	RemoteDriver(Driver *drv, Socket *socket) :
			Driver(drv->getLocation(), drv->getStatus(), drv->getId(), drv->getAge(),
					drv->getExperience(), drv->getMap())
	{
		soc = socket;
	};
	virtual ~RemoteDriver()
	{
		delete soc;
	}
	void setCab(Cab* cab);
	void setTrip(Trip* trip);
	void setMap(Map *map);
	void setExperience(int years);
	void startDriving();
	void stopWorking();
	void setSocket(Socket* sock){ soc = sock;};
	//Driver moves one step in it's Trip.
	void moveOneStep(unsigned int time);
};

#endif /* REMOTEDRIVER_H_ */
