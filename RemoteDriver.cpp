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

template<class T> string RemoteDriver::serializeObj(T* obj)
{
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
	currentTrip = trip;
	location = trip->getRoadStart();
	// TODO support this in the future
	//	soc->sendData((char)Client::Actions::setTrip + serializeObj(trip));
	soc->sendData(serializeObj(trip));
}

void RemoteDriver::stopWorking()
{
	isDriverDriving = false;
	currentTrip = NULL;
	soc->sendData((char)Client::shutDown + string("shutDown"));
}

void RemoteDriver::moveOneStep(unsigned int time)
{
	// big enough to hold all numbers up to 64 bytes and '\0', Client::Actions::moveOneStep
	char buff[22];
	unsigned int movment;
	// First we will check if the time is past the Trip's starting time.
	if (currentTrip->getStartingTime() >= time)
	{
		buff[0] = (char)Client::moveOneStep;
		sprintf(buff + 1, "%020d", time);
		soc->sendData(buff);
		//We are past the starting time so moveOneStep.
		movment = myCab->getMovmentAbility();
		this->location = this->currentTrip->advance(movment);
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
//void RemoteDriver::startDriving()
//{
//}
