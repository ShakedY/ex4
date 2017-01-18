/*
 * TaxiCenter.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_TAXICENTER_H_
#define SRC_TAXICENTER_H_
#include <list>
#include <pthread.h>
#include "../bfs/BFSObject.h"
#include "../bfs/BFSPoint.h"
#include "../cabs/Cab.h"
#include "../map/Map.h"
#include "../map/Trip.h"
#include "../map/Passenger.h"
#include "../drivers/Driver.h"
#include "../threads/GlobalInfo.h"
#include "../threads/TripsCalcThread.h"
#include <pthread.h>
class Trip;
class Driver;
class Passenger;
class Map;

/*
 * This is the TaxiCenter class,it will manage all the control flow
 * between the cabs,drivers and trips,it will hold lists of all the trips
 * cabs and drivers and manage the connections that will be made between them.
 */
class TaxiCenter
{
//Private members of this class.
private:
	//List of all the drivers.
	std::list<Driver*> drivers;
	//List of all the cabs.
	std::list<Cab*> cabs;
	//List of all the trips.
	std::list<Trip*> trips;
	//Map that we will assign to the drivers.
	Map* map;
	//Current time of the world.
	unsigned int time;
	static TaxiCenter* instance;
	/*
		 * Constructor of the TaxiCenter,it will get the map of the world as it's input
		 * and create an empty list of cabs,drivers and trips that will be filled when the user
		 * will enter one of the trips cabs or drivers,it will also set the time to be 0 to start
		 * the program.We made the constructor private because we will use it while implementing
		 * the threads so we will get the TaxiCenter via static method.
		 */
		TaxiCenter(Map *m) :
				drivers(), cabs(), trips(), map(m), time(0)
		{
			std::list<Cab*> cabs;
			std::list<Driver*> drivers;
			std::list<Trip*> trips;
		}
		;
public:
	/*struct Calculation {
		Trip* myTrip;
		Map* myMap;
	};*/
	static TaxiCenter* getInstance(Map *m = NULL);
	/*
	 * Destructor of the TaxiCenter,it will delete all of the drivers,cabs and trips
	 * that were assigned to the program from the user.
	 */
	virtual ~TaxiCenter();
	/*
	 * Add a driver to the list of drivers.
	 */
	void addDriver(Driver* driv);
	/*
	 * Add a cab to the list of cabs.
	 */
	void addCab(Cab* cab);
	/*
	 * Add a trip to the list of trips.
	 */
	void addTrip(Trip* trip);
	/*
	 * Add more than one driver to the list of drivers.
	 */
	void addDrivers(std::list<Driver*> drivs);
	/*
	 * Add more than one cab to the list of cabs.
	 */
	void addCabs(std::list<Cab*> cabs);

	/*
	 * Attach the map of the world to all the drivers in the TaxiCenter.
	 */
	void attachMaptoDrivers(Map* map);

	/*
	 * Attach available trips to the available drivers in the TaxiCenter.
	 */
	void attachDriversToTrips();

	/*
	 * Attach cabs to available drivers in the TaxiCenter.
	 */
	void attachCabsToDrivers();

	/*
	 * Shut down the taxi center.Tell all drivers to stop working.
	 */
	void endWorking();

	//Send a taxi to a passenger.
	//TODO use this function maybe in later exercises.
	void sendTaxi(const BFSPoint* source, const BFSPoint* destination);
	void sendTaxi(Passenger* passenger);

	/*
	 * Get location of the driver with the id in the input.
	 */
	const Point* getDriverLocation(int driverId) const;

	//Get the list of drivers of the TaxiCenter.
	std::list<Driver*> getDriversList() const;

	//Get the list of cabs of the TaxiCenter.
	std::list<Cab*> getCabsList() const;

	//Get the cab with the entered id.
	Cab* getCab(int cabId) const;

	//Get current time of our world.
	int getCurrentTime();

	//Move all the drivers with trips by one step.
	void moveAllOneStep();

	// like a list of worker at an company
	std::list<const Driver*>* getDrivers() const;
	/*
	 * This method will be called from each thread of the client,it will set the trips for
	 * the drivers.
	 */
	static void* setRoadFromThread(void* params);
};

#endif /* SRC_TAXICENTER_H_ */
