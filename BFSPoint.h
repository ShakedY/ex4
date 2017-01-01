/*
 * BFSPoint.h
 *
 *  Created on: Nov 26, 2016
 *      Author: adi
 */

#ifndef BFSPOINT_H_
#define BFSPOINT_H_

#include "BFSObject.h"
#include "Point.h"

#include <iostream>
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
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>


class BFSPoint : public BFSObject
{
private:
	Point point;
	unsigned numOfAdjacent;
	BFSPoint *adjacent1, *adjacent2, *adjacent3, *adjacent4;
	friend class boost::serialization::access;
	//Set back inline function that we will use during serialization.
	inline void setBack(BFSPoint* value,BFSPoint* first,BFSPoint* second,BFSPoint* third,
						BFSPoint* fourth);
public:
	/*
	 * constructor method
	 * initialize BFSpoint object
	 * the input neighbors will be saved in the order "first non NULL", and between the non NULL input
	 * neighbors the inputs order will be kept(adjacent_i will be the i-th non NULL pointer).
	 */
	BFSPoint(int x = 0, int y = 0, BFSPoint* neighbor1 = NULL,
		BFSPoint* neighbor2 = NULL, BFSPoint* neighbor3 = NULL,
		BFSPoint* neighbor4 = NULL);

	/*
	 * setting BFSpoint object
	 * initialize BFSpoint object
	 * the input neighbors will be saved in the order "first non NULL", and between the non NULL input
	 * neighbors the inputs order will be kept(adjacent_i will be the i-th non NULL pointer).
	 */
	void set(int x = 0, int y = 0, BFSPoint* neighbor1 = NULL,
			BFSPoint* neighbor2 = NULL, BFSPoint* neighbor3 = NULL,
			BFSPoint* neighbor4 = NULL);
	/*
	 * setting BFSpoint object
	 * changing BFSpoint object.
	 * the input neighbors will be saved in the order "first non NULL", and between the non NULL
	 * input neighbors the inputs order will be kept(adjacent_i will be the i-th non NULL pointer).
	 */
	void setNeighbors(BFSPoint * neighbor1, BFSPoint * neighbor2,
			BFSPoint * neighbor3, BFSPoint * neighbor4);

	Point getPoint();
	/*
	* return x axis
	*/
	int getX() const;
	/*
	* return y axis
	*/
	int getY() const;
	virtual ~BFSPoint()
	{
	}
	;
	unsigned getNumbersOfNeighbors() const
	{
		return numOfAdjacent;
	}
	/*
	 * Receiving a list of pointers to BFSObjects and adding to the list pointers to our neighbors.
	 * Getting all non NULL neighbors into the list. The neighbors are added to the head of
	 * the list starting from the last neighbor to preserve the neighbors order(lists are LIFO)
	 */
	void adjacent(std::list<BFSObject*>& lst);
	/*
	 * The method copies the members of "other" to this object.
	 */
	BFSPoint& operator=(const BFSPoint& other);
	/*
	 * The method copies the point of "other" to this object point member.
	 */
	const Point& operator=(const Point& other);
	/*
	 * operator overloading of ==
	 * comparing the 2 BFSPoint objects members, if all equals then
	 * returns true, otherwise return false.
	 */
	bool operator==(const BFSPoint& other) const;
	/*
	 * The method compares the BFSPoint point member to the input point, returns true if they're
	 * equal and false otherwise.
	 */
	friend bool operator==(const Point& p, const BFSPoint& bp);
	/*
	 * The method compares the BFSPoint point member to the input point, returns true if they're
	 * equal and false otherwise.
	 */
	friend bool operator==(const BFSPoint& bp, const Point& p);
	/*
	 * operator overloading of <<
	 * adding to the stream the point.
	 */
	friend std::ostream& operator<<(std::ostream& out, const BFSPoint& bp);
	/*
	 * operator overloading of <<
	 * adding to the stream the point.
	 */
	friend std::ostream& operator<<(std::ostream& out,
			const BFSPoint * const bp);
	/*
	 * Serialization method for BFSPoint class, we will use it while
	 * transfering objects between the client and the server.
	 */
	template<class Archive>
	void serialize(Archive & ar,const unsigned int version);
};

#endif /* BFSPOINT_H_ */
