/*
 * GlobalInfo.h
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#ifndef GLOBALINFO_H_
#define GLOBALINFO_H_
#include "Trip.h"
#include "Cab.h"
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
	GlobalInfo(int numDrivers);
	vector<Trip*> trips;
	vector<Cab*> cabs;
	bool ended;
public:
	static GlobalInfo* getInstance(int numDrivers = 0);
	Trip* getIthTrip(int i);
	Cab* getIthCab(int i);
	void setIthTrip(int i,Trip* trip);
	void setIthCab(int i,Cab* cab);
	void endThreads();
	bool toExit();
};

#endif /* GLOBALINFO_H_ */
