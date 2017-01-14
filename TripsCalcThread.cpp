/*
 * TripsCalcThread.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#include "TripsCalcThread.h"
TripsCalcThread* TripsCalcThread::instance  = NULL;

TripsCalcThread::TripsCalcThread() {
	// TODO Auto-generated constructor stub

}
TripsCalcThread* TripsCalcThread::getInstance() {
	if (!instance) {
		instance = new TripsCalcThread();
	}
	return instance;
}

void TripsCalcThread::addTripId(int id) {
	trip_ids.push_back(id);
}

void TripsCalcThread::addThread(pthread_t thread) {
	calcThreads.push_back(thread);
}

pthread_t TripsCalcThread::getThreadOfTrip(int id) {
	return calcThreads[id];
}

TripsCalcThread::~TripsCalcThread() {
	// TODO Auto-generated destructor stub
}

