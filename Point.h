/*
 * Point.h
 *
 *  Created on: Nov 16, 2016
 *      Author: adi
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <string>
#include <cstdio>
class Point
{
private:
	int x, y;
	/*
	* returns the number of digits in an int
	*/
	inline unsigned numOfDigits(int n) const;
public:
	/*
	* constructor method
	* initialize point object
	* @param integer of x axis, integer of y axis
	*/
	Point(int xAxis, int yAxis);
	/*
	* return x axis
	*/
	int getX() const;
	/*
	* return y axis
	*/
	int getY() const;
	/*
	* return string representation of the point in the format (x,y)
	*/
	std::string toString() const;
	/*
	* operator overloading of =
	* copies the input point x,y.
	*/
	Point& operator=(const Point& other);
	/*
	 * operator overloading of ==
	 * comparing the 2 Point objects members, if all equals then
	 * returns true, otherwise return false.
	 */
	bool operator==(const Point& other) const;
	/*
	* operator overloading of <<
	* add the point to the stream as a string in the format (x,y).
	*/
	friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

#endif /* POINT_H_ */
