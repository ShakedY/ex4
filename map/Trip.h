/*
 * Trip.h
 *
 *  Created on: Dec 3, 2016
 *      Author: Adi
 */

#ifndef SRC_TRIP_H_
#define SRC_TRIP_H_
#include <boost/serialization/list.hpp>
#include "Passenger.h"
#include "Map.h"
#include "../bfs/Point.h"
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
class Passenger;


/*
 * The Trip class will represent a trip that the driver passes through between
 * a start point and an end point.
 */
class Trip
{
private:
	int rideId, meters, numOfPassengers;
	unsigned int startingTime;
	double tariff;
	//Start and end points.
	Point startPoint, endPoint;
	std::list<const Passenger*> passengers;
	std::list<Point> road;
	//Iterator for current position in the trip.
	std::list<Point>::iterator currentPosition;

	//Use for boost's serialization.
	friend class boost::serialization::access;

	/*
	 * We will use this function to serialize a trip with boost's library.
	 */
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
	}
public:
	//Default constructor of this class.
	Trip() :
			rideId(0), meters(0), numOfPassengers(0), startingTime(0), tariff(
					0.0), startPoint(0, 0), endPoint(0, 0), passengers(), road()
	{
	};

	/*
	 * Constructor which gets the id of the trip,number of passengers,tariff and
	 * start and end points.
	 */
	Trip(int id, int numOfPass, const BFSPoint *start, const BFSPoint *end, double tar) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start->getPoint();
		endPoint = end->getPoint();
		tariff = tar;
		startingTime = 0;
	};

	//Same as the constructor above,just describe points as Point class and not BFSPoint.
	Trip(int id, int numOfPass, const Point& start, const Point& end, double tar) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start;
		endPoint = end;
		tariff = tar;
		startingTime = 0;
	}
	;
	/*
	 * Constructor after adding starting time parameter.
	 */
	Trip(int id, int numOfPass, const BFSPoint* start, const BFSPoint* end, double tar,
			int startTime) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start->getPoint();
		endPoint = end->getPoint();
		tariff = tar;
		startingTime = startTime;
	}
	;
	/*
	 * Constructor after adding starting time with points.
	 */
	Trip(int id, int numOfPass, const Point& start, const Point& end, double tar,
			int startTime) :
			passengers(), road()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start;
		endPoint = end;
		tariff = tar;
		startingTime = startTime;
	};

	//Add a passenger to this trip.
	void addPassenger(const Passenger *passenger);

	//Add a list of passengers.
	void addPassengers(std::list<const Passenger*> passengers);

	//Get satisfaction of the passengers.
	double getPassengersSatisfaction() const;

	//Get id of this trip.
	int getId() const;

	//Get length in meters of this trip.
	int getMeters() const;

	//Get starting point of this trip.
	const Point& getStart() const;

	//Get ending point of this trip.
	const Point& getEnd() const;

	//Advance the iterator of the trip by given distance.
	const Point* advance(unsigned int distance);

	//Get the number of passengers.
	int getNumOfPassengers() const;

	//Get the tariff of this trip.
	int getTariff() const;

	//Get the starting time of this trip.
	unsigned int getStartingTime();

	//Set the road of this trip by using the map.
	void setRoad(Map* m);

	//Assign the iterator to the beginning of the trip.
	void restartTrip();
};

#endif /* SRC_TRIP_H_ */
