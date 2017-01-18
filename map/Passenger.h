/*
 * Passenger.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_
#include "../bfs/BFSPoint.h"

/*
 * This is the passenger class,it will represent the people in the world that are passed
 * to different locations with the trip.
 */
//TODO use this class in later assignments,irrelevant now.
class Passenger
{
private:
	//Source and destination points.
	BFSPoint source;
	BFSPoint destination;
public:
	//Default constructor of this class.
	Passenger() :
			source(), destination()
	{
	};
	/* A constructor that allow us to make a connection between the map and the passengers
	 * without the passenger knowing about it
	 */
	Passenger(const BFSPoint *src, const BFSPoint *dest)
	{
		source = *src;
		destination = *dest;
	};

	/*
	 * A constructor of the passenger which gets two points for the source and destination
	 * points of the passenger.
	 */
	Passenger(const Point& src, const Point& dest)
	{
		source = src;
		destination = dest;
	}

	/*
	 * Constructor which gets a BFSPoint and a point for the source and destination.
	 */
	Passenger(const BFSPoint *src, const Point& dest)
	{
		source = *src;
		destination = dest;
	}

	/*
	 * Constructor which gets a Point and a BFSPoint for the source and destination.
	 */
	Passenger(const Point& src, const BFSPoint *dest)
	{
		source = src;
		destination = *dest;
	}

	//Get the source of the passenger.
	const BFSPoint* getSource() const;

	//Get the destination of the passenger.
	const BFSPoint* getDestination() const;

	//Let the passenger produce a review about it's ride.
	double produceTripReview() const;
	// TODO fix include bugs
//	void callTaxiCenter(TaxiCenter* taxiCenter);
};

#endif /* SRC_PASSENGER_H_ */
