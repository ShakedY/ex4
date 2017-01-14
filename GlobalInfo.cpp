/*
 * GlobalInfo.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: lior
 */

#include "GlobalInfo.h"
//Set the static instance member to be NULL.
GlobalInfo* GlobalInfo::instance  = NULL;

GlobalInfo::GlobalInfo(int numDrivers) {
	//Allocate two arrays of pointers to trips and cabs.
	//Initialize vectors to be NULL.
	trips = vector<Trip*>(numDrivers);
	cabs = vector<Cab*>(numDrivers);
	for (int i = 0;i < numDrivers;i++) {
		trips[i] = NULL;
		cabs[i] = NULL;
	}
	ended = false;

}

void GlobalInfo::endThreads() {
	ended = true;
}

bool GlobalInfo::toExit() {
	return ended;
}
GlobalInfo* GlobalInfo::getInstance(int numDrivers) {
	if (!instance) {
		//Create the instance.
		instance = new GlobalInfo(numDrivers);
	}
	return instance;
}

Trip* GlobalInfo::getIthTrip(int i) {
	return trips[i];
}

Cab* GlobalInfo::getIthCab(int i) {
	return cabs[i];
}

void GlobalInfo::setIthTrip(int i,Trip* trip) {
	trips[i] = trip;
}

void GlobalInfo::setIthCab(int i,Cab* cab) {
	//cout <<"Setting cab for id: " << i << endl;
	cabs[i] = cab;
}
GlobalInfo::~GlobalInfo() {
	// TODO Auto-generated destructor stub
}

