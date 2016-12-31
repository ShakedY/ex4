/*
 * BFSPoint.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: adi
 */

#include "BFSPoint.h"
using namespace std;
// gets a target pointer and 4 pointers, assign to target the first non NULL pointer(or NULL if
// all pointers are NULL), then change the the first non NULL pointer to NULL.
#define FIRST_NON_NULL_AND_CHANGE_TO_NULL(target, a, b, c, d)	{		\
									if (a != NULL)						\
									{									\
										target = a;						\
										a = NULL;						\
									}									\
									else if (b != NULL)					\
									{									\
										target = b;						\
										b = NULL;						\
									}									\
									else if (c != NULL)					\
									{									\
										target = c;						\
										c = NULL;						\
									}									\
									else								\
									{									\
										target = d;						\
										d = NULL;						\
									}									\
								};										\


BFSPoint::BFSPoint(int x, int y, BFSPoint* neighbor1, BFSPoint* neighbor2,
		BFSPoint* neighbor3, BFSPoint* neighbor4) :
		BFSObject(), point(x, y)
{
	// numOfAdjacent grow by 1 for every non-NULL neighbor
	numOfAdjacent = (neighbor1 != NULL) + (neighbor2 != NULL)
			+ (neighbor3 != NULL) + (neighbor4 != NULL);
	/* dividing the neighbors to the adjacent so the first
	 * adjacent(index-wise) won't be NULL. In other words:
	 * 		adjacent_i can be NULL <--> adjacent_(i+1) is NULL
	 * vacuous truth: adjacent5 := adjacent_5 := NULL. */
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent1, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent2, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent3, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent4, neighbor1, neighbor2,
			neighbor3, neighbor4);
}

void BFSPoint::set(int x, int y, BFSPoint* neighbor1, BFSPoint* neighbor2,
		BFSPoint* neighbor3, BFSPoint* neighbor4)
{
	point = Point(x, y);
	// numOfAdjacent grow by 1 for every non-NULL neighbor
	numOfAdjacent = (neighbor1 != NULL) + (neighbor2 != NULL)
			+ (neighbor3 != NULL) + (neighbor4 != NULL);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent1, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent2, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent3, neighbor1, neighbor2,
			neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent4, neighbor1, neighbor2,
			neighbor3, neighbor4);
}

void BFSPoint::setNeighbors(BFSPoint * neighbor1, BFSPoint * neighbor2,
		BFSPoint * neighbor3, BFSPoint * neighbor4)
{
	numOfAdjacent = (neighbor1 != NULL) + (neighbor2 != NULL)
			+ (neighbor3 != NULL) + (neighbor4 != NULL);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent1, neighbor1, neighbor2, neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent2, neighbor1, neighbor2, neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent3, neighbor1, neighbor2, neighbor3, neighbor4);
	FIRST_NON_NULL_AND_CHANGE_TO_NULL(adjacent4, neighbor1, neighbor2, neighbor3, neighbor4);
}

int BFSPoint::getX() const
{
	return point.getX();
}

int BFSPoint::getY() const
{
	return point.getY();
}

void BFSPoint::adjacent(list<BFSObject*>& lst)
{
	switch (numOfAdjacent)
	{
	case 4:
		lst.push_front(adjacent4);
	case 3:
		lst.push_front(adjacent3);
	case 2:
		lst.push_front(adjacent2);
	case 1:
		lst.push_front(adjacent1);
		break;
	default:
	{
		break;
	}
	}
}

BFSPoint& BFSPoint::operator=(const BFSPoint& other)
{
	this->point = other.point;
	this->numOfAdjacent = other.numOfAdjacent;
	this->adjacent1 = other.adjacent1;
	this->adjacent2 = other.adjacent2;
	this->adjacent3 = other.adjacent3;
	this->adjacent4 = other.adjacent4;
	return *this;
}

const Point& BFSPoint::operator=(const Point& other)
{
	point = other;
	return other;
}

bool BFSPoint::operator==(const BFSPoint& other) const
{
	bool flag = (this->point == other.point);
	flag &= (this->numOfAdjacent == other.numOfAdjacent);
	flag &= (this->adjacent1 == other.adjacent1);
	flag &= (this->adjacent2 == other.adjacent2);
	flag &= (this->adjacent3 == other.adjacent3);
	flag &= (this->adjacent4 == other.adjacent4);
	return flag;
}

bool operator==(const Point& p, const BFSPoint& bp)
{
	return p == bp.point;
}

bool operator==(const BFSPoint& bp, const Point& p)
{
	return p == bp.point;
}

ostream& operator<<(ostream& out, const BFSPoint& bp)
{
	out << bp.point;
	return out;
}

ostream& operator<<(ostream& out, const BFSPoint * const bp)
{
	out << bp->point;
	return out;
}

Point BFSPoint::getPoint()
{
	return point;
}
