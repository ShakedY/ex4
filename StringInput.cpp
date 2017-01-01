
#include "StringInput.h"
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "BFSPoint.h"
#define IS_DIGIT(character) ((character >= '0') && (character <= '9'))
#define IS_MARITAL_

using namespace::std;

StringInput::StringInput(int argNum, char* args[]) {
	// TODO Auto-generated constructor stub
	argc = argNum;
	argv = args;
	gridInfo.obstacles = NULL;
}

StringInput::~StringInput() {
	delete gridInfo.obstacles;
}

void StringInput::readMapInfo() {
	list<Point> *obstacles = new list<Point>();
	int x, y, obstaclesNumber;
	//cout << "Insert the grid size: (Example: 3 3)" << endl;
	scanf("%d", &x);
	scanf("%d", &y);
	gridInfo.width = x;
	gridInfo.height = y;

	//test
	if (x != y) {
		cerr << "The grid should be same x,y, your input was " << x << "," << y << endl;
		throw invalid_argument("The grid should have the same height and width");
	}

	//cout << "Insert the num of obstacles" << endl;
	scanf("%d", &obstaclesNumber);
	for (int i = 0; i < obstaclesNumber; i++) {
		//cout << "Insert obstacle " << i << " information" << endl;
		scanf("%d,%d", &x, &y);
		obstacles->push_front(Point(x, y));
	}
	if(gridInfo.obstacles != NULL)
		delete gridInfo.obstacles;
	gridInfo.obstacles = obstacles;
}

void StringInput::getDriverInfo() {
	int id, age, experience, vehicle_id;//, count = 0;
	char status;
/*	unsigned int i = 0;
	string info;

	//cout << "Insert driver info" << endl;
	cin.ignore();
	getline(cin, info);
	while (i < info.size())
	{
		int addToIndex = 1;

		if (info[i] != ',') {

			if (count == 0)
			{
				string subString = info.substr(i, info.find(","));
				addToIndex = subString.length();
				id = getNumber(subString);
			}
			if (count == 1)
			{
				string subString = info.substr(i, info.find(",", i) - i);
				addToIndex = subString.length();
				age = getNumber(subString);
			}
			if (count == 2)
			{
				status = info[i];
			}
			if (count == 3)
			{
				string subString = info.substr(i, info.find(",", i) - i);
				addToIndex = subString.length();
				experience = getNumber(subString);
			}
			if (count == 4)
			{
				string subString = info.substr(i, info.find(",", i) - i);
				addToIndex = subString.length();
				vehicle_id = getNumber(subString);
			}
		}
		else
			count++;

		i += addToIndex;
	}*/
	scanf("%d,%d,%c,%d,%d", &id, &age, &status, &experience, &vehicle_id);

	driverInfo.id = id;
	driverInfo.age = age;
	driverInfo.stat = status;
	driverInfo.yearsOfExperience = experience;
	driverInfo.cabId = vehicle_id;
}

void StringInput::getCabInfo() {
	int id;//, count = 0;
	int taxi_type;
	char manufacturer;
	char color;
	scanf("%d,%d,%c,%c", &id, &taxi_type, &manufacturer, &color);
	cabInfo.id = id;
	cabInfo.taxi_type = (taxi_type == 1)? (Cab::STANDARD):(Cab::LUXURY);
	cabInfo.manufacturer = (Cab::Manufacturer)manufacturer;
	cabInfo.color = (Cab::cabColor)color;
}

void StringInput::getTripInfo() {
	int id, x_start, y_start, x_end, y_end, num_passengers,time;
	double tariff;
	scanf("%d,%d,%d,%d,%d,%d,%lf,%d", &id, &x_start, &y_start, &x_end, &y_end,
			&num_passengers, &tariff,&time);
	//Set up all the members of tripInfo struct.
	tripInfo.id = id;
	tripInfo.x_start = x_start;
	tripInfo.y_start = y_start;
	tripInfo.x_end = x_end;
	tripInfo.y_end = y_end;
	tripInfo.num_passengers = num_passengers;
	tripInfo.tariff = tariff;
	tripInfo.time = time;
}



