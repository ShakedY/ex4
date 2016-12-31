/*
 * BFSObject.h
 *
 *  Created on: Nov 26, 2016
 *      Author: adi
 */

#ifndef BFSOBJECT_H_
#define BFSOBJECT_H_

#include <queue>
#include <list>
#include <string>

class BFSObject
{
// first public is just for enum types
public:
	typedef enum
	{
		WHITE, BLACK
	} Color;
protected:
	Color color;
	size_t distance;
	BFSObject* parent;
public:
	BFSObject() :
			color(WHITE), distance(-1), parent(NULL)
	{
	}
	;
	virtual ~BFSObject()
	{
	}
	;
	/*
	* return distance(edges-wise) from the BFS root
	*/
	std::size_t getDistance() const;
	/*
	* return the parent of in the BFS tree
	*/
	BFSObject* getParent() const;
	/*
	* prepare a list of pointers to BFSObject for a new BFS. This is a mandatory method, and shouldn't
	* be use if the user want to keep previous BFS data. If all the objects BFS data variables are
	* with their default value, this method is unnecessary.
	*/
	void BFSInitialization(std::list<BFSObject*>& nodes);
	/*
	*  main BFS algorithm. The method runs the BFS algorithm with the caller
	*  object as its root.
	*  written according to function represented in the book -
	*  Introduction to algorithms by Thomas H. Cormen, Charles E. Leiserson,
	*  Ronald L. Rivest, and Clifford Stein.
	*/
	void BFS();
	virtual void adjacent(std::list<BFSObject*>& lst)=0;
};

#endif /* BFSOBJECT_H_ */
