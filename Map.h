/*
 * Map.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_
#include <list>
#include "BFSPoint.h"
#include "Trip.h"

class Trip;
#define SIZE 10
// the grid Y axis are the opposite of the array lines indexes
#define INDEX_TO_Y_AXIS(index, size)		(size - 1  - index)	// max_y - index
#define Y_AXIS_TO_INDEX(y, size)		(size - 1  - y)		// max_index - y

class Map
{
private:
	unsigned int dimX, dimY;
	/* The grid Y axis are like an array lines and the grid X axis are
	 * like the array columns. */
	BFSPoint grid[SIZE][SIZE];
	std::list<BFSPoint*> obstacles;
protected:
	BFSPoint* getTheLocation(const BFSPoint& p);
public:
	Map() :
			dimX(0), dimY(0)
	{
	}
	;
	Map(unsigned int witdh, unsigned int height, std::list<BFSPoint*>& obstacles);
	Map(unsigned int witdh, unsigned int height, std::list<Point>& obstacles);
	Map(unsigned int witdh, unsigned int height);
	virtual ~Map()
	{
	};

	// TODO consider leaving the Trip creation logic to the map user instead of crating it here
	Trip* calcTrip(const BFSPoint& source, const BFSPoint& destination);
	void calculateShortestPath(std::list<const BFSPoint*>& path, const BFSPoint& source,
			const BFSPoint& destination);
	const BFSPoint* getTheLocation(unsigned x, unsigned y) const;
	const BFSPoint* getTheLocation(const Point& p) const;
	void giveToAllMapUsersTheirDistanceFrom(unsigned x, unsigned y);
};

#endif /* SRC_MAP_H_ */
