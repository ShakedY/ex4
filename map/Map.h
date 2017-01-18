/*
 * Map.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_
#include <list>
#include "../bfs/BFSPoint.h"
//#include "Trip.h"

//class Trip;
#define SIZE 1000
// the grid Y axis are the opposite of the array lines indexes
#define INDEX_TO_Y_AXIS(index, size)		(size - 1  - index)	// max_y - index
#define Y_AXIS_TO_INDEX(y, size)		(size - 1  - y)		// max_index - y

/*
 * This is our Map class,it will represent the Map which is given to all the drivers in our
 * world.We will implement the singleton design pattern because we want only one map in
 * our program.
 */
class Map
{
private:
	pthread_mutex_t lock;
	unsigned int dimX, dimY;
	/* The grid Y axis are like an array lines and the grid X axis are
	 * like the array columns. */
	BFSPoint grid[SIZE][SIZE];
	std::list<BFSPoint*> obstacles;
	//All of our constructors will be private.
	Map() :
				dimX(0), dimY(0)
		{
		}
		;
		Map(unsigned int witdh, unsigned int height, std::list<BFSPoint*>& obstacles);
		Map(unsigned int witdh, unsigned int height, std::list<Point> obstacles);
		Map(unsigned int witdh, unsigned int height);
	static Map* instance;
	void set_for_new_thread();
protected:
	BFSPoint* getLocationPrivate(const BFSPoint& p);
	BFSPoint* getLocationPrivate(const Point& p);

public:
	/*
	 * Get the instance of the Map that we have in the program if there isn't one
	 * it will create one by calling the private constructor and if there is it will
	 * return the static instance which is saved in this class.
	 */
	static Map* getInstance(unsigned int width = 0,unsigned int height = 0,
			std::list<Point> obstacles = std::list<Point>());
	virtual ~Map()
	{
		pthread_mutex_destroy(&lock);
	};

	// TODO consider leaving the Trip creation logic to the map user instead of crating it here
	//Calculate the patg between two points by using the BFS algorithm.
	void calculateShortestPath(std::list<const BFSPoint*>& path, const BFSPoint& source,
			const BFSPoint& destination);
	void calculateShortestPath(std::list<Point>& path, const Point& source,
			const Point& destination);
	//Get the location of the input in a BFSPoint object.
	const BFSPoint* getTheLocation(unsigned x, unsigned y) const;
	const BFSPoint* getTheLocation(const Point& p) const;
	//Update all the users of the map with the given instance.
	void giveToAllMapUsersTheirDistanceFrom(unsigned x, unsigned y);
	int getWidth();
	int getHeight();
};

#endif /* SRC_MAP_H_ */
