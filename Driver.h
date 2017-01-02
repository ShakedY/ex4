/*
 * Driver.h
 *
 *  Created on: Dec 3, 2016
 *      Author: Adi
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include "BFSPoint.h"
#include "Cab.h"
#include "Trip.h"
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
		ar & isAvailableforAnotherTrip;
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
	bool isAvailableforAnotherTrip;
	char status;
	double averageStisfaction;
	Cab* myCab;
	Trip* currentTrip;
	const Point* location, *dest;
	Map* myMap;

public:
	virtual ~Driver()
	{
		// In the case where this driver was assigned with a trip delete it cause TaxiCenter
		// won't have this trip assigned in it's lists.
		delete currentTrip;
	}
	;
	Driver()
	{
		id = 0;
		age = 0;
		yearsOfExperience = 0;
		numOfReivewsGotten = 0;
		isAvailableforAnotherTrip = true;
		status = 0;
		averageStisfaction = 0.0;
		myCab = NULL;
		currentTrip = NULL;
		location = NULL;
		dest = NULL;
		myMap = NULL;
	}
	;
	Driver(const BFSPoint* loc, char stat, int id, int age,
			int yearsOfExperience, Map *m);
	Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab, Map *m);
	bool hasCab() const;
	bool isAvailable() const;
	void addReview(double rating);
	virtual void setCab(Cab* cab);
	virtual void setTrip(Trip* trip);
	void setMap(Map *map);
	void setExperience(int years);
	virtual void stopWorking();
	const Point* getLocation() const;
	const Trip* getTrip() const;
	double getAvgSatisfaction() const;
	int getId() const;
	char getStatus() const;
	int getAge() const;
	int getExperience() const;
	//Get the cab of the driver.
	Cab* getCab() const;
	Map* getMap() const;
	//Driver moves one step in it's Trip.
	virtual void moveOneStep();
	unsigned getDistanceFromSource()
	{
		return myMap->getTheLocation(*location)->getDistance();
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
