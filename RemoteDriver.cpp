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
	char action = (char)Client::setTrip;
	currentTrip = trip;
	//Set trip to be taken.
	cout <<"HERE?" << endl;
	trip->setIsTaken();
	location = trip->getRoadStart();
	cout <<"Here???" << endl;
	// TODO support this in the future
	//	soc->sendData((char)Client::Actions::setTrip + serializeObj(trip));
	soc->sendData(&action);
	cout <<"After here" << endl;
	soc->sendData(serializeObj(trip));
}

void RemoteDriver::stopWorking()
{
	isDriverDriving = false;
	currentTrip = NULL;
	soc->sendData((char)Client::shutDown + string("shutDown"));
}

int RemoteDriver::moveOneStep(unsigned int time)
{
	// big enough to hold all numbers up to 64 bytes and '\0', Client::Actions::moveOneStep
	char buff[4];
	char action;
	cout << "Here moving one step in RemoteDriver" << endl;
	unsigned int movment;
	// First we will check if the time is past the Trip's starting time.
	if (currentTrip->getStartingTime() < time)
	{

		action = (char)Client::moveOneStep;
		soc->sendData(&action);
		sprintf(buff, "%d", time);
		cout << "Sending string " << buff << endl;
		soc->sendData(buff);
		//We are past the starting time so moveOneStep.
		movment = myCab->getMovmentAbility();
		cout <<"Here advancing the trip" << endl;
		this->location = this->currentTrip->advance(movment);
		if (location == this->currentTrip->getRoadEnd()) {
			//Return 0 cause we ended this trip.
			cout <<"HEREEEEEE" << endl;
			return 0;
		} else {
			//We can move on from this location in the trip.
			return 1;
		}
	}
	//There is a trip but it didn't begin,we will still move later.
	return 1;
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
