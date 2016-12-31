/*
 * Passenger.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#include "Passenger.h"
#include <cstdlib>

const BFSPoint* Passenger::getSource() const
{
	return &source;
}

const BFSPoint* Passenger::getDestination() const
{
	return &destination;
}

double Passenger::produceTripReview() const
{
	double rating = ((double) rand()) / RAND_MAX + rand() % 5;
	return rating;
}

void Passenger::callTaxiCenter(TaxiCenter* taxiCenter)
{
	taxiCenter->sendTaxi(&source, &destination);
}

