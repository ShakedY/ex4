/*
 * Trip.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_TRIP_H_
#define SRC_TRIP_H_
#include <list>
#include "Passenger.h"
#include "Point.h"
class Passenger;

class Trip
{
private:
	int rideId, meters, numOfPassengers;
	Point startPoint, endPoint;
	double tariff;
	std::list<const Passenger*> passengers;
	bool isTaken;
public:
	Trip() :
			rideId(0), meters(0), numOfPassengers(0), startPoint(0,0), endPoint(0,0), tariff(
					0.0), passengers(), isTaken(false)
	{
	}
	;
	Trip(int id, int numOfPass, BFSPoint *start, BFSPoint *end,
			double tar) :
				startPoint(0,0), endPoint(0,0), passengers()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start->getPoint();
		endPoint = end->getPoint();
		tariff = tar;
		isTaken = false;
	}
	Trip(int id, int numOfPass, Point& start, Point& end,
			double tar) :
				startPoint(0,0), endPoint(0,0), passengers()
	{
		rideId = id;
		meters = 0;
		numOfPassengers = numOfPass;
		startPoint = start;
		endPoint = end;
		tariff = tar;
		isTaken = false;
	}
	void addPassenger(const Passenger *passenger);
	void addPassengers(std::list<const Passenger*> passengers);
	double getPassengersSatisfaction() const;
	int getId() const;
	int getMeters() const;
	const Point& getStart() const;
	const Point& getEnd() const;
	int getNumOfPassengers() const;
	int getTariff() const;
	bool isTripTaken() const;
	void setIsTaken();
	void movedPoint(unsigned int distance);
};

#endif /* SRC_TRIP_H_ */
