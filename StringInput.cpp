
/*
 * InputAnalizer.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: assaf
 */

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
/*	unsigned int i = 0;
	string info;


	//cout << "Set cab info" << endl;
	cin.ignore();
	getline(cin, info);
	while (i < info.size())
	{
		int addToIndex = 1;

		if (info[i] != ',')
		{
			if (count == 0)
			{
				string subString = info.substr(i, info.find(","));
				addToIndex = subString.length();
				id = getNumber(subString);
			}
			if (count == 1)
			{
				string subString = info.substr(i, info.find(","));
				taxi_type = getNumber(subString);
			}
			if (count == 2)
				manufacturer = (Cab::Manufacturer)info[i];
			if (count == 3)
				color = (Cab::cabColor)info[i];
		}
		else
			count++;

		i += addToIndex;
	}*/

	scanf("%d,%d,%c,%c", &id, &taxi_type, &manufacturer, &color);
	cabInfo.id = id;
	cabInfo.taxi_type = (taxi_type == 1)? (Cab::STANDARD):(Cab::LUXURY);
	cabInfo.manufacturer = (Cab::Manufacturer)manufacturer;
	cabInfo.color = (Cab::cabColor)color;
}

void StringInput::getTripInfo() {
	int id, x_start, y_start, x_end, y_end, num_passengers;//, count = 0;
	double tariff;
/*	unsigned int i = 0;
	string info;

	//cout << "Set trip info" << endl;
	cin.ignore();
	getline(cin, info);
	while (i < info.size())
	{
		int addToIndex = 1;

		if (info[i] != ',') {
			int c = info.find(",", i) - i;
			string subString = info.substr(i, c);
			addToIndex = subString.length();

			if (count == 0)
			{
				id = getNumber(subString);
			}
			if (count == 1)
			{
				x_start = getNumber(subString);
			}
			if (count == 2)
				y_start = getNumber(subString);
			if (count == 3)
				x_end = getNumber(subString);
			if (count == 4)
				y_end = getNumber(subString);
			if (count == 5)
				num_passengers = getNumber(subString);
			if (count == 6)
			{
				tariff = getDoubleNumber(subString);
				break;
			}
		}
		else
			count++;

		i += addToIndex;
	}*/

	scanf("%d,%d,%d,%d,%d,%d,%lf", &id, &x_start, &y_start, &x_end, &y_end,
			&num_passengers, &tariff);
	tripInfo.id = id;
	tripInfo.x_start = x_start;
	tripInfo.y_start = y_start;
	tripInfo.x_end = x_end;
	tripInfo.y_end = y_end;
	tripInfo.num_passengers = num_passengers;
	tripInfo.tariff = tariff;
}


/*
 * Function name: stringToInt
 * The input: string, integer pointer
 * The output: integer representation of the string
 * The Function operation: updating to the integer pointer inserted
 *  the number length and return the integer representation of the string
 */
//void getObstaclePoint(const string& s, int *prefix_size, int *x, int *y)
//{
//	int i = 0;
//	enum Flag
//	{
//		POSITIVE = 0, NEGATIVE = 1
//	};
//	*prefix_size = 0;
//	for (int j = 0; j < 2; j++) {
//		i += *prefix_size;
//		Flag flag = (s[i] != '-') ? (POSITIVE) : (NEGATIVE);
//		// i starts as flag value to determine the index of the first digit
//		int n = 0;
//		i += flag;
//		while (IS_DIGIT(s[i]))
//		{
//			n = n * 10 + s[i] - '0';
//			++i;
//		}
//		if (flag == NEGATIVE)
//		{
//			n = -n;
//		}
//		// checking that the prefix isn't just "-" or "-00...0" before determining
//		// the size of the longest valid number prefix of "s"
//		*prefix_size = (!flag || n != 0) ? (i) : (0);
//		//i++;
//		if (j == 0)
//			*x = n;
//		if (j == 1)
//			*y = n;
//	}
//}

/*
 * Function name: vaildated_and_analize_input
 * The input: character pointer, array of integers
 * The output: boolean value
 * The Function operation: checking
 *  the number length and return the integer representation of the string
 */
/*void getObstaclePoint(const string& input,int *x,int *y)
{
string* str = &input;
int prefix_size;
*x=stringToInt(input,&prefix_size);
str = str + prefix_size+1;
*y=stringToInt(input,&prefix_size);
}*/

//int StringInput::getNumber(string info) {
//	unsigned int i = 0, n = 0;
//	while (i < info.length()){
//		n *= 10;
//		n += info[i++] - '0';
//	}
//
//	return n;
//}

//double StringInput::getDoubleNumber(string info) {
//	unsigned int i = 0, count = 0;
//	bool isAfterDecimalPart = false;
//	double n = 0.0;
//	while (i < info.length()) {
//		if (info[i] == '.')
//			isAfterDecimalPart = true;
//		if (!isAfterDecimalPart)
//			n = n * 10 + (info[i] - '0');
//		else {
//			count++;
//			n = n + (info[i] - '0') / count;
//		}
//
//		i++;
//	}
//
//	return n;
//}
