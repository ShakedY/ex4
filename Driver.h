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
class Map;
class Passenger;
class Trip;
class Cab;

class Driver
{
// first public is just for enum defining
public:
	enum MaritalStatus
	{
		SINGLE = 'S',
		MARRIED = 'M',
		DIVORCED = 'D',
		WIDOWED = 'W'
	};

private:
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
public:
	virtual ~Driver()
	{
	};
	Driver(const BFSPoint* loc, char stat, int id, int age, int yearsOfExperience, Map *m);
	Driver(int id, int age, char stat, int yearsOfExperience, Cab* cab, Map *m) ;
	bool hasCab() const;
	bool isDriving() const;
	void addPassenger(const Passenger *passenger);
	void removePassenger(const Passenger *passenger);
	void addReview(double rating);
	void assignCab(Cab* cab);
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
	unsigned getDistanceFromSource()
	{
		return this->location->getDistance();
	}
};

#endif /* SRC_DRIVER_H_ */
