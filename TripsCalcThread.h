/*
 * TripsCalcThread.h
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#ifndef TRIPSCALCTHREAD_H_
#define TRIPSCALCTHREAD_H_
#include <vector>
#include <pthread.h>
using namespace std;
/*
 * We will use this class to get matching of each trip to it's thread.
 */
class TripsCalcThread {

private:
	TripsCalcThread();
	//Members will be the id's of the trips and the threads which handle the claculation.
	vector<int> trip_ids;
	vector<pthread_t> calcThreads;
	static TripsCalcThread* instance;
public:
	static TripsCalcThread* getInstance();
	void addTripId(int id);
	void addThread(pthread_t thread);
	pthread_t getThreadOfTrip(int id);
	virtual ~TripsCalcThread();
};

#endif /* TRIPSCALCTHREAD_H_ */
