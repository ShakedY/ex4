/*
 * Trip.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_TRIP_H_
#define SRC_TRIP_H_
#include "Passenger.h"
#include "Map.h"
#include "Point.h"
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
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/list.hpp>


class Passenger;
class Map;

class Trip
{
private:
	int rideId, meters, numOfPassengers;
	unsigned int startingTime;
	double tariff;
	Point startPoint, endPoint;
	std::list<const Passenger*> passengers;
	std::list<const BFSPoint*> road;
	std::list<const BFSPoint*>::iterator currentPosition;
	bool isTaken;
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & rideId;
		ar & meters;
		ar & numOfPassengers;
		ar & startingTime;
		ar & tariff;
		ar & startPoint;
		ar & endPoint;
		// TODO add Passenger support but for now they are irrelevant
		ar & road;
		ar & currentPosition;
		ar & isTaken;
	}
public:
	Trip() :
			rideId(0), meters(0), numOfPassengers(0), startingTime(0), tariff(
					0.0), startPoint(0, 0), endPoint(0, 0), passengers(), road(), isTaken(
					false)
	{
	}
	;
	Trip(int id, int numOfPass, BFSPoint *start, BFSPoint *end, double tar) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start->getPoint();
		endPoint = end->getPoint();
		tariff = tar;
		isTaken = false;
		startingTime = 0;
	}
	;
	Trip(int id, int numOfPass, Point& start, Point& end, double tar) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start;
		endPoint = end;
		tariff = tar;
		isTaken = false;
		startingTime = 0;
	}
	;
	/*
	 * Constructor after adding starting time parameter.
	 */
	Trip(int id, int numOfPass, BFSPoint* start, BFSPoint* end, double tar,
			int startTime) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start->getPoint();
		endPoint = end->getPoint();
		tariff = tar;
		isTaken = false;
		startingTime = startTime;
	}
	;
	/*
	 * Constructor after adding starting time with points.
	 */
	Trip(int id, int numOfPass, Point& start, Point& end, double tar,
			int startTime) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start;
		endPoint = end;
		tariff = tar;
		isTaken = false;
		startingTime = startTime;
	}
	;
	void addPassenger(const Passenger *passenger);
	void addPassengers(std::list<const Passenger*> passengers);
	double getPassengersSatisfaction() const;
	int getId() const;
	int getMeters() const;
	const Point& getStart() const;
	const Point& getEnd() const;
	const BFSPoint* getRoadStart() const;
	const BFSPoint* getRoadEnd() const;
	int getNumOfPassengers() const;
	int getTariff() const;
	bool isTripTaken() const;
	void setIsTaken();
	const BFSPoint* advence(unsigned int distance);
	unsigned int getStartingTime();
	void setRoad(Map* m);
	const std::list<const BFSPoint*>& getRoad();
};

#endif /* SRC_TRIP_H_ */
