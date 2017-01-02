/*
 * Passenger.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_
#include "BFSPoint.h"
//#include "TaxiCenter.h"
//class TaxiCenter;

class Passenger
{
private:
	BFSPoint source;
	BFSPoint destination;
public:
	Passenger() :
			source(), destination()
	{
	}
	;
	/* a constructor that allow us to make a connection between the map and the passengers
	 * without the passenger knowing about it */
	Passenger(const BFSPoint *src, const BFSPoint *dest)
	{
		source = *src;
		destination = *dest;
	}
	Passenger(const Point& src, const Point& dest)
	{
		source = src;
		destination = dest;
	}
	Passenger(const BFSPoint *src, const Point& dest)
	{
		source = *src;
		destination = dest;
	}
	Passenger(const Point& src, const BFSPoint *dest)
	{
		source = src;
		destination = *dest;
	}
	const BFSPoint* getSource() const;
	const BFSPoint* getDestination() const;
	double produceTripReview() const;
	// TODO fix include bugs
//	void callTaxiCenter(TaxiCenter* taxiCenter);
};

#endif /* SRC_PASSENGER_H_ */
