/*
 * BFSObject.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: adi
 */

#include "BFSObject.h"

using namespace boost::archive;
using namespace std;


size_t BFSObject::getDistance() const
{
	return distance;
}

BFSObject* BFSObject::getParent() const
{
	return parent;
}

void BFSObject::BFSInitialization(list<BFSObject*>& nodes)
{
	// the BFS initialization
	BFSObject *node;
	while (!nodes.empty())
	{
		node = nodes.front();
		nodes.pop_front();
		node->color = WHITE;
		node->distance = -1;
		node->parent = NULL;
	}
}

void BFSObject::BFS()
{
	// variable declaration
	queue<BFSObject*> q;
	list<BFSObject*> neighbors;
	size_t d;
	BFSObject *root, *neighbor;

	// the BFS tree root setup
	parent = this;
	color = BLACK;
	distance = 0;
	q.push(this);

	/* the BFS main logic */
	do
	{
		root = q.front();
		q.pop();
		d = root->distance + 1;
		root->adjacent(neighbors);
		while (!neighbors.empty())
		{
			neighbor = neighbors.front();
			neighbors.pop_front();
			if (neighbor->color == WHITE)
			{
				neighbor->color = BLACK;
				neighbor->distance = d;
				neighbor->parent = root;
				q.push(neighbor);
			}
		}
	} while (!q.empty());
}
template<class Archive>
void BFSObject::serialize(Archive & ar,const unsigned int version) {
	ar & color;
	ar & distance;
	ar & parent;
}


template<class Archive>
void BFSObject::serialize(Archive & ar,const unsigned int version) {
	ar & color;
	ar & distance;
	ar & parent;
}

