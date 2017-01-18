/*
 * BFSObject.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: adi
 */

#include "BFSObject.h"

using namespace boost::archive;
using namespace std;

void BFSObject::set_for_new_thread()
{
	pthread_t id = pthread_self();
	struct states temp;
	temp.color = WHITE;
	temp.distance = (size_t) -1;
	temp.parent = NULL;
	info[id] = temp;
}

void BFSObject::set_for_new_thread(pthread_t id)
{
	struct states temp;
	temp.color = WHITE;
	temp.distance = (size_t) -1;
	temp.parent = NULL;
	info[id] = temp;
}

size_t BFSObject::getDistance() const
{
	pthread_t id = pthread_self();
	return (*(info.find(id))).second.distance;
}

BFSObject* BFSObject::getParent() const
{
	pthread_t id = pthread_self();
	return (*(info.find(id))).second.parent;
}

void BFSObject::BFSInitialization(list<BFSObject*>& nodes)
{
	// the BFS initialization
	struct states clear;
	clear.color = WHITE;
	clear.distance = -1;
	clear.parent = NULL;
	pthread_t id = pthread_self();
	BFSObject *node;
	list<BFSObject*>::iterator it = nodes.begin(), end = nodes.end();
	for (; it != end; ++it)
	{
		node = *it;
		node->info[id].color = WHITE;
		node->info[id].distance = -1;
		node->info[id].parent = NULL;
	}
}

void BFSObject::BFS()
{
	// variable declaration
	pthread_t id = pthread_self();
	queue<BFSObject*> q;
	list<BFSObject*> neighbors;
	size_t d;
	BFSObject *root, *neighbor;

	// the BFS tree root setup
	info[id].parent = this;
	info[id].color = BLACK;
	info[id].distance = 0;
	q.push(this);

	/* the BFS main logic */
	do
	{
		root = q.front();
		q.pop();
		d = root->info[id].distance + 1;
		root->adjacent(neighbors);
		while (!neighbors.empty())
		{
			neighbor = neighbors.front();
			neighbors.pop_front();
			if (neighbor->info[id].color == WHITE)
			{
				neighbor->info[id].distance = d;
				neighbor->info[id].color = BLACK;
				neighbor->info[id].parent = root;
				q.push(neighbor);
			}
		}
	} while (!q.empty());
}
