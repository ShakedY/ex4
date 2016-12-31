/*
 * Point.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: adi
 */

#include "Point.h"
using namespace std;

Point::Point(int xAxis, int yAxis)
{
	x = xAxis;
	y = yAxis;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

string Point::toString() const
{
	// 3 for (,), another 3 for the null terminator and the possible sign("-")
	unsigned const size = 3 + 3 + numOfDigits(x) + numOfDigits(y);
	char buff[size];
	sprintf(buff, "(%d,%d)", x, y);
	string s(buff);
	return s;
}

inline unsigned Point::numOfDigits(int n) const
{
	unsigned digits = 0;
	do
	{
		++digits;
		n /= 10;
	} while (n != 0);
	return digits;
}

Point& Point::operator =(const Point& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

ostream& operator <<(ostream& out, const Point& p)
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

bool Point::operator ==(const Point& other) const
{
	return (x==other.x)&&(y==other.y);
}
