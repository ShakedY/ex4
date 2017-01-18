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
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

/*
 * This is the Point class,in our case the world is a 2 dimensional space so a
 * Point will represent a location in our world with two indexes.
 */
class Point
{
private:
	int x, y;

	/*
	 * Returns the number of digits in an int
	 */
	inline unsigned numOfDigits(int n) const;
	//Use for boost's serialization.
	friend class boost::serialization::access;
public:
	/*
	 * Constructor method
	 * initialize point object
	 * @param integer of x axis, integer of y axis
	 */
	Point(int xAxis, int yAxis);
	/*
	 * Default constructor.
	 */
	Point() :
			x(0), y(0)
	{
	}
	;
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
	/*
	 * Serialization of point class,we will use it while serializing other classes which
	 * use the Point class.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & x;
		ar & y;
	}
	;
};

#endif /* POINT_H_ */
