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
	friend class boost::serialization::access;
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
	/*
	 * Serialization of this object,we will use it while serializing derived
	 * classes.
	 */
	template<class Archive>
	void serialize(Archive & ar,const unsigned int version) {
		ar & color;
		ar & distance;
		ar & parent;
	}
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(BFSObject);
#endif /* BFSOBJECT_H_ */
