/*
 * RemoteDriver.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: adi-peled
 */

#include "RemoteDriver.h"

RemoteDriver::RemoteDriver(const BFSPoint* loc, char stat, int id, int age,
		int yearsOfExperience, Map *m, Socket *socket) :
		Driver(loc, stat, id, age, yearsOfExperience, m)
{
	soc = socket;
}

RemoteDriver::RemoteDriver(Driver *drv, Socket *socket) :
		Driver()
{
	location = drv->location;
	status = drv->status;
	id = drv->id;
	age = drv->age;
	yearsOfExperience = drv->yearsOfExperience;
	myMap = drv->myMap;
	soc = socket;
}

template<class T> string RemoteDriver::serializeObj(T* obj)
{
	//Serialize an object same as recitations examples.
	std::string serial_str;
	boost::iostreams::back_insert_device<std::string> inserter(serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
			inserter);
	boost::archive::binary_oarchive oa(s);
	oa << obj;
	s.flush();
	return serial_str;
}

template<class T>
T* RemoteDriver::deSerializeObj(const char* serial_str, int size)
{
	//Deserialize an object same as recitations examples.
	T* obj;
	boost::iostreams::basic_array_source<char> device(serial_str, size);
	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
			device);
	boost::archive::binary_iarchive ia(s);
	ia >> obj;
	return obj;
}

void RemoteDriver::setCab(Cab* cab)
{
	myCab = cab;
	soc->sendData(serializeObj(cab));
}

void RemoteDriver::setTrip(Trip* trip)
{
	delete currentTrip;
	currentTrip = trip;
	location = &(currentTrip->getStart());
	dest = &(currentTrip->getEnd());
	//Restart iterator of trip.
	trip->restartTrip();
	isAvailableforAnotherTrip = false;
	soc->sendData((char)Client::setTrip);
	soc->sendData(serializeObj(trip));
}

void RemoteDriver::stopWorking()
{
	char ack;
	isAvailableforAnotherTrip = true;
	soc->sendData((char)Client::shutDown);
	// waiting ack from the client to close
	soc->reciveData(&ack, 1);
}

void RemoteDriver::moveOneStep()
{
	// if we have a job
	if (!isAvailableforAnotherTrip)
	{
		this->location = this->currentTrip->advance(myCab->getMovmentAbility());
		soc->sendData((char)Client::moveOneStep);
		isAvailableforAnotherTrip = *dest == *location;
	}
}

// TODO when TCP is allowed replace the movement logic and when location is
// requested just ask through the socket
// const BFSPoint* RemoteDriver::getLocation() const;

//void RemoteDriver::setMap(Map* map)
//{
//	// new map means starting over at (0,0)
//	this->myMap = map;
//	this->location = map->getTheLocation(Point(0,0));
//	soc->sendData(serializeObj(location));
//}
//
//void RemoteDriver::setExperience(int years)
//{
//}
//

