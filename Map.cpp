

#include "Map.h"
#include <stdlib.h>
#include <stdexcept>
using namespace std;

Map::Map(unsigned int width, unsigned int height, list<BFSPoint*>& obstacles)
{
	bool flag = false;
	if (width <= 10 && height <= 10)
	{
		if (width > 0 && height > 0)
		{
			dimX = width;
			dimY = height;
		}
		else
		{
			throw invalid_argument("height and width of map should be a positive number");
		}
	}
	else
	{
		throw invalid_argument("height and width of map should be 10 at most");
	}
	BFSPoint *node, *neighbor1, *neighbor2, *neighbor3, *neighbor4;
	unsigned int y;

	// initialization of the grid
	for (unsigned int i = 0; i < dimY; ++i)
	{
		y = INDEX_TO_Y_AXIS(i, dimY);
		for (unsigned int x = 0; x < dimX; ++x)
		{
			// Finding the neighbors clockwise (9,12,3,6)
			node = &grid[i][x];

			// If root has a point to the left(array-wise) who's on the grid
			neighbor1 = (x > 0)? (node - 1):(NULL);

			// If the root has a point above(array-wise) him who's on the grid
			// if so, going up(array-wise) a whole row
			neighbor2 = (i > 0)? (node - SIZE):(NULL);

			// If root has a point to the right(array-wise) who's on the grid
			neighbor3 = (x + 1 < dimX)? (node + 1):(NULL);

			// If the root has a point below(array-wise) him who's on the grid
			// if so, going down(array-wise) a whole row
			neighbor4 = (i + 1 < dimY)? (node + SIZE):(NULL);

			// initialization of the node
			for (unsigned int j = 0; j < obstacles.size(); j++)
			{
				for (std::list<BFSPoint*>::iterator it = obstacles.begin();
						it != obstacles.end(); ++it)
				{
					if ((((unsigned) (*it)->getX()) == x)
							&& (((unsigned) (*it)->getY()) == y))
					{
						flag = true;
					}
				}
			}
			if (flag == false)
				node->set(x, y, neighbor1, neighbor2, neighbor3, neighbor4);
		}

	}
}

Map::Map(unsigned int width, unsigned int height, list<Point>& obstacles)
{
	if (width <= 10 && height <= 10)
	{
		if (width > 0 && height > 0)
		{
			dimX = width;
			dimY = height;
		}
		else
		{
			throw invalid_argument("height and width of map should be a positive number");
		}
	}
	else
	{
		throw invalid_argument("height and width of map should be 10 at most");
	}
	BFSPoint *node, *neighbor1, *neighbor2, *neighbor3, *neighbor4;
	int y;

	// initialization of the grid
	for (unsigned int i = 0; i < dimY; ++i)
	{
		y = INDEX_TO_Y_AXIS(i, dimY);
		for (unsigned int x = 0; x < dimX; ++x)
		{
			// Finding the neighbors clockwise (9,12,3,6)
			node = &grid[i][x];

			// If root has a point to the left(array-wise) who's on the grid
			neighbor1 = (x > 0)? (node - 1):(NULL);

			// If the root has a point above(array-wise) him who's on the grid
			// if so, going up(array-wise) a whole row
			neighbor2 = (i > 0)? (node - SIZE):(NULL);

			// If root has a point to the right(array-wise) who's on the grid
			neighbor3 = (x + 1 < dimX)? (node + 1):(NULL);

			// If the root has a point below(array-wise) him who's on the grid
			// if so, going down(array-wise) a whole row
			neighbor4 = (i + 1 < dimY)? (node + SIZE):(NULL);

			// initialization of the node
			node->set(x, y, neighbor1, neighbor2, neighbor3, neighbor4);
		}
	}

	// removing unreachable points
	list<Point>::iterator obstacle = obstacles.begin(), end = obstacles.end();
	list<BFSObject*>::iterator a_neighbor, finish;
	list<BFSObject*> neighbors, the_neighbor_neighbors;
	BFSPoint *temp, *obs;
	for (; obstacle != end; ++obstacle)
	{
		obs = &grid[Y_AXIS_TO_INDEX(obstacle->getY(), dimY)][obstacle->getX()];
		obs->adjacent(neighbors);

		a_neighbor = neighbors.begin();
		finish = neighbors.end();
		for (; a_neighbor != finish; ++a_neighbor)
		{
			(*a_neighbor)->adjacent(the_neighbor_neighbors);

			neighbor1 = neighbor2 = neighbor3 = neighbor4 = NULL;

			switch (((BFSPoint*) (*a_neighbor))->getNumbersOfNeighbors())
			{
				case 4:
					temp = (BFSPoint*) the_neighbor_neighbors.front();
					the_neighbor_neighbors.pop_front();
					neighbor1 = (temp != obs)? (temp):(NULL);
				case 3:
					temp = (BFSPoint*) the_neighbor_neighbors.front();
					the_neighbor_neighbors.pop_front();
					neighbor2 = (temp != obs)? (temp):(NULL);
				case 2:
					temp = (BFSPoint*) the_neighbor_neighbors.front();
					the_neighbor_neighbors.pop_front();
					neighbor3 = (temp != obs)? (temp):(NULL);
				case 1:
					temp = (BFSPoint*) the_neighbor_neighbors.front();
					the_neighbor_neighbors.pop_front();
					neighbor4 = (temp != obs)? (temp):(NULL);
				default:
					break;
			}
			((BFSPoint*) (*a_neighbor))->setNeighbors(neighbor1, neighbor2,
					neighbor3, neighbor4);
		}
		neighbors.clear();
	}
}

Map::Map(unsigned int width, unsigned int height)
{
	if (width <= 10 && height <= 10)
	{
		if (width > 0 && height > 0)
		{
			dimX = width;
			dimY = height;
		}
		else
		{
			throw invalid_argument("height and width of map should be a positive number");
		}
	}
	else
	{
		throw invalid_argument("height and width of map should be 10 at most");
	}
	BFSPoint *node, *neighbor1, *neighbor2, *neighbor3, *neighbor4;
	int y;

	// initialization of the grid
	for (unsigned int i = 0; i < dimY; ++i)
	{
		y = INDEX_TO_Y_AXIS(i, dimY);
		for (unsigned int x = 0; x < dimX; ++x)
		{
			// Finding the neighbors clockwise (9,12,3,6)
			node = &grid[i][x];

			// If root has a point to the left(array-wise) who's on the grid
			neighbor1 = (x > 0)? (node - 1):(NULL);

			// If the root has a point above(array-wise) him who's on the grid
			// if so, going up(array-wise) a whole row
			neighbor2 = (i > 0)? (node - SIZE):(NULL);

			// If root has a point to the right(array-wise) who's on the grid
			neighbor3 = (x + 1 < dimX)? (node + 1):(NULL);

			// If the root has a point below(array-wise) him who's on the grid
			// if so, going down(array-wise) a whole row
			neighbor4 = (i + 1 < dimY)? (node + SIZE):(NULL);

			// initialization of the node
			node->set(x, y, neighbor1, neighbor2, neighbor3, neighbor4);
		}
	}
}

Trip* Map::calcTrip(const BFSPoint& source, const BFSPoint& destination)
{
	BFSPoint *src = getTheLocation(source), *dst = getTheLocation(destination);
	Trip *trip = new Trip(rand(), 0, src, dst, 49.99, 0); // only 49.99! sale!!
	return trip;
}

void Map::calculateShortestPath(list<const BFSPoint*>& path,
		const BFSPoint& source, const BFSPoint& destination)
{
	BFSPoint *src = getTheLocation(source);
	BFSObject *dst = (BFSObject*) getTheLocation(destination);
	if (src->getDistance() != 0)
		src->BFS();
	do
	{
		path.push_front((BFSPoint*) dst);
		dst = dst->getParent();
	} while (dst != src);
	path.push_front(src);
}

const BFSPoint* Map::getTheLocation(unsigned x, unsigned y) const
{
	if (x >= dimX || y >= dimY)
	{
		throw invalid_argument("location not on the map");
	}
	return &grid[Y_AXIS_TO_INDEX(y, dimY)][x];
}

BFSPoint* Map::getTheLocation(const BFSPoint& p)
{
	unsigned int x = (unsigned) p.getX(), y = (unsigned) p.getY();
	if (x >= dimX || y >= dimY)
	{
		throw invalid_argument("location not on the map");
	}
	return &grid[Y_AXIS_TO_INDEX(y, dimY)][x];
}

const BFSPoint* Map::getTheLocation(const Point& p) const
{
	unsigned int x = (unsigned) p.getX(), y = (unsigned) p.getY();
	if (x >= dimX || y >= dimY)
	{
		throw invalid_argument("location not on the map");
	}
	return &grid[Y_AXIS_TO_INDEX(y, dimY)][x];
}

void Map::giveToAllMapUsersTheirDistanceFrom(unsigned x, unsigned y)
{
	grid[Y_AXIS_TO_INDEX(y, dimY)][x].BFS();
}
