/*
 * TripsCalcThread.h
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#ifndef TRIPSCALCTHREAD_H_
#define TRIPSCALCTHREAD_H_
#include <map>
#include <pthread.h>
using namespace std;
/*
 * We will use this class to get matching of each trip to it's thread.
 */
class TripsCalcThread {

private:
	TripsCalcThread();
	//Members will be the id's of the trips and the threads which handle the claculation.
	std::map<int, pthread_t> calcThreads;
	static TripsCalcThread* instance;
public:
	/*
	 * Implement a static getInstance class to use the singleton of the design pattern,
	 * we want only one instance of TripsCalcThread in the program.
	 */
	static TripsCalcThread* getInstance();
	//Add a thread for a specific trip id to the program.
	void addThread(pthread_t thread, int id);
	//Get the thread of a specific trip id.
	pthread_t getThreadOfTrip(int id);
	virtual ~TripsCalcThread();
};

#endif /* TRIPSCALCTHREAD_H_ */
