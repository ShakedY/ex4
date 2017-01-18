/*
 * TripsCalcThread.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#include "TripsCalcThread.h"
TripsCalcThread* TripsCalcThread::instance = NULL;

TripsCalcThread::TripsCalcThread():
		calcThreads()
{
	// TODO Auto-generated constructor stub
}

TripsCalcThread* TripsCalcThread::getInstance()
{
	if (!instance)
	{
		instance = new TripsCalcThread();
	}
	return instance;
}

#include <iostream>
void TripsCalcThread::addThread(pthread_t thread, int id)
{
	calcThreads[id] = thread;
}

pthread_t TripsCalcThread::getThreadOfTrip(int id)
{
	return calcThreads[id];
}

TripsCalcThread::~TripsCalcThread()
{
	// TODO Auto-generated destructor stub
}

