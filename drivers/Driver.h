/*
 * Driver.h
 *
 *  Created on: Dec 3, 2016
 *      Author: Adi
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include "../bfs/BFSPoint.h"
#include "../cabs/Cab.h"
#include "../map/Trip.h"
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

/*
 * The Driver class will represent the driver in our world,this class
 * will hold the drivers Cab and Trip and will implement several functions which
 * will help the driver travel through the trip's that it's given.
 */
class Driver
{
private:
	//We will use boost serialization so be friend of the access.
	friend class boost::serialization::access;
	//Be a friend of the RemoteDriver function which we will use for communication in the server.
	friend class RemoteDriver;
	//Be a friend of the Client access to give it access to this class.
	friend class Client;

	/*
	 * This is the serialization method that we used while serializing this object
	 * with boost's serialization.
	 */
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
// First public is just for enum defining
public:
	enum MaritalStatus
	{
		SINGLE = 'S', MARRIED = 'M', DIVORCED = 'D', WIDOWED = 'W'
	};

protected:
	int id, age, yearsOfExperience;
	unsigned numOfReivewsGotten;
	bool isAvailableforAnotherTrip;
	bool has_cab;
	char status;
	double averageStisfaction;
	//Cab of this driver.
	Cab* myCab;
	//Trip of this driver.
	Trip* currentTrip;
	//Driver's location and ending destination of trip.
	Point location;
	const Point *dest;
	//The map of the world.
	Map* myMap;

public:
	//Destructor of this class.
	virtual ~Driver()
	{
		// In the case where this driver was assigned with a trip delete it cause TaxiCenter
		// won't have this trip assigned in it's lists.
		delete currentTrip;
	}
	;
	//Default constructor of this class,set members to random values.
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
		location = Point(0,0);
		dest = NULL;
		myMap = NULL;
	}
	;
	/*
	 * Constructor for this class which will get the location of the Driver as a BFSPoint
	 * the driver's status,it's id,age,years of experience and the world's map.
	 */
	Driver(const BFSPoint* loc, char stat, int id, int age,
			int yearsOfExperience, Map *m);
	/*
	 * Constructor which will get the cab of the driver instead of it's location.
	 */
	Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab, Map *m);

	//Method that will tell us if a driver already has a cab.
	bool hasCab() const;

	//Method that will tell us if a driver is available for a trip.
	bool isAvailable() const;

	//A method that assigns the satisfaction of the passengers to the driver.
	void addReview(double rating);

	/*
	 * Set a cab for this driver,this method will be virtual cause we will override it when
	 * we will implement classes that derive from this class.
	 */
	virtual void setCab(Cab* cab);

	/*
	 *Set a trip for this driver,this method will be virtual cause we will override it when
	 * we will implement classes that derive from this class.
	 */
	virtual void setTrip(Trip* trip);

	//Set the map of this world to as a private member of this driver.
	void setMap(Map *map);

	//Set the years of experience.
	void setExperience(int years);

	//Set this driver to be available for another trip.
	virtual void stopWorking();

	//Get the location of this driver.
	const Point* getLocation() const;

	//Get the trip of this driver.
	const Trip* getTrip() const;

	//Get the average satisfaction of passengers from this driver.
	double getAvgSatisfaction() const;

	//Get the ID of this driver.
	int getId() const;

	//Get the status of this driver.
	char getStatus() const;

	//Get this driver's age.
	int getAge() const;

	//Get the years of experience this driver has.
	int getExperience() const;

	//Get the cab of the driver.
	Cab* getCab() const;

	//Get the map of this world from the driver.
	Map* getMap() const;

	/*
	 * Move one step in the trip of this driver,this method will be virtual cause we will
	 * override it in the classes that derive from this class.
	 */
	virtual void moveOneStep();

	//Get the distance from the source.
	unsigned getDistanceFromSource()
	{
		return myMap->getTheLocation(location)->getDistance();
	}

	// Operator overloading for << operator of output stream.
    friend std::ostream& operator<< (std::ostream &os, const Driver &p)
    {
		os << "{ id:" << p.id << "," << "age:" << p.age << "," <<
				"years of experince" << p.yearsOfExperience << "," <<
				"num of reviews gotten:" << p.numOfReivewsGotten << ","
				<< "status:" << p.status << "," << "stisfaction" <<
				p.averageStisfaction << "," << "location:" << "}";
		return os;
    }
    //Set this driver to be available or unavailabel for a Trip.
    void setAvailable(bool);

};

#endif /* SRC_DRIVER_H_ */
