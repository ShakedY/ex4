/*
 * GlobalInfo.h
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#ifndef GLOBALINFO_H_
#define GLOBALINFO_H_
#include "../map/Trip.h"
#include "../cabs/Cab.h"
#include <vector>
using namespace std;
/*
 * This class will have the global information that we will use
 * to implement the communication between the main thread and other threads.
 * In order to make it global we will use the singleton design pattern so there could
 * be an access to it's instantiation from everywhere in the code.
 */
class GlobalInfo {
private:
	virtual ~GlobalInfo();
	static GlobalInfo* instance;
	/*
	 * The constructor of this class will be private because we implement the singleton design
	 * pattern so that this class only instance in the program will be created only from inside
	 * the class in the getInstance method.
	 */
	GlobalInfo(int numDrivers);
	//Vectors for the trips and the cabs.
	vector<Trip*> trips;
	vector<Cab*> cabs;
	//Boolean to tell threads the program is done in the main thread.
	bool ended;
public:
	/*
	 * Get the static instance of this class,we used the singleton design pattern so that there
	 * will be only one GlobalInfo throughout the program and all the threads can have access
	 * to it with this static method.
	 */
	static GlobalInfo* getInstance(int numDrivers = 0);
	//Get the Ith trip for our vector.
	Trip* getIthTrip(int i);
	//Get the Ith cab from our vector.
	Cab* getIthCab(int i);
	//Set the Ith trip in our vector.
	void setIthTrip(int i,Trip* trip);
	//Set the Ith cab in our vector.
	void setIthCab(int i,Cab* cab);
	//Tell the threads to end.
	void endThreads();
	//Return the ended boolean.
	bool toExit();
};

#endif /* GLOBALINFO_H_ */
