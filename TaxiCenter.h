/*
 * TaxiCenter.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_TAXICENTER_H_
#define SRC_TAXICENTER_H_
#include <list>
#include "BFSObject.h"
#include "BFSPoint.h"
#include "Cab.h"
#include "Map.h"
#include "Passenger.h"
#include "Driver.h"
class Driver;
class Passenger;
class Map;

class TaxiCenter
{
private:
	std::list<Driver*> drivers;
	std::list<Cab*> cabs;
	std::list<Trip*> trips;
	Map* map;
public:
	TaxiCenter(Map *m) :
		drivers(), cabs(), trips(), map(m)
	{
		std::list<Cab*> cabs;
		std::list<Driver*> drivers;
		std::list<Trip*> trips;
	}
	;
	virtual ~TaxiCenter();
	void addDriver(Driver* driv);
	void addCab(Cab* cab);
	void addTrip(Trip* trip);
	void addDrivers(std::list<Driver*> drivs);
	void addCabs(std::list<Cab*> cabs);
	void sendTaxi(const BFSPoint* source, const BFSPoint* destination);
	const BFSPoint* getDriverLocation(int driverId);// const;
	void attachMaptoDrivers(Map* map);
	void attachDriversToTrips();
	void attachCabsToDrivers();
//	void startWorking();
	void endWorking();
	void sendTaxi(Passenger* passenger);
//	bool checkingIfDriving(Driver* driver);// const;
	std::list<Driver*> getDriversList() const;
	std::list<Cab*> getCabsList() const;
	Cab* getCab(int cabId) const;
};

#endif /* SRC_TAXICENTER_H_ */
