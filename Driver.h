/*
 * Driver.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include "BFSPoint.h"
#include "Cab.h"
#include "Trip.h"
#include "Map.h"
#include "Passenger.h"

#include <iostream>
#include <fstream>
#include <sstream>
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

using namespace std;
using namespace boost::archive;

class Map;
class Passenger;
class Trip;
class Cab;

class Driver
{
private:
	friend class boost::serialization::access;
	friend class RemoteDriver;
	friend class Client;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & id;
		ar & age;
		ar & yearsOfExperience;
		ar & numOfReivewsGotten;
		ar & isDriverDriving;
		ar & status;
		ar & averageStisfaction;
		ar & myCab;
	}
// first public is just for enum defining
public:
	enum MaritalStatus
	{
		SINGLE = 'S', MARRIED = 'M', DIVORCED = 'D', WIDOWED = 'W'
	};

protected:
	int id, age, yearsOfExperience;
	unsigned numOfReivewsGotten;
	bool isDriverDriving;
	char status;
	double averageStisfaction;
	Cab* myCab;
	Trip* currentTrip;
	const BFSPoint *location;
	Map* myMap;
	std::list<const Passenger*> passengers;
	std::list<const BFSPoint*> road;

public:
	virtual ~Driver()
	{
	}
	;
	Driver() :
		passengers()
	{
		id = 0;
		age = 0;
		yearsOfExperience = 0;
		numOfReivewsGotten = 0;
		isDriverDriving = false;
		status = 0;
		averageStisfaction = 0.0;
		myCab = NULL;
		currentTrip = NULL;
		location = NULL;
		myMap = NULL;
	}
	;
	Driver(const BFSPoint* loc, char stat, int id, int age,
			int yearsOfExperience, Map *m);
	Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab, Map *m);
	bool hasCab() const;
	bool isDriving() const;
	void addPassenger(const Passenger *passenger);
	void removePassenger(const Passenger *passenger);
	void addReview(double rating);
	void setCab(Cab* cab);
	void setTrip(Trip* trip);
	void setMap(Map *map);
	void setExperience(int years);
	void startDriving();
	void stopWorking();
	const BFSPoint* getLocation() const;
	const Trip* getTrip() const;
	double getAvgSatisfaction() const;
	int getId() const;
	int getAge() const;
	int getExperience() const;
	//Get the cab of the driver.
	Cab* getCab() const;
	//Get Trip of the driver
	Trip* getTrip();
	//Driver moves one step in it's Trip.
	void moveOneStep(unsigned int time);
	unsigned getDistanceFromSource()
	{
		return this->location->getDistance();
	}

	// friends
    friend std::ostream& operator<< (std::ostream &os, const Driver &p)
    {
		os << "{ id:" << p.id << "," << "age:" << p.age << "," <<
				"years of experince" << p.yearsOfExperience << "," <<
				"num of reviews gotten:" << p.numOfReivewsGotten << ","
				<< "status:" << p.status << "," << "stisfaction" <<
				p.averageStisfaction << "," << "location:" << "}";
		return os;
    }

};

#endif /* SRC_DRIVER_H_ */
