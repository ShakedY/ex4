/*
 * Cab.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_CAB_H_
#define SRC_CAB_H_
#include "BFSPoint.h"
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

/*
 * This is the cab class,it will have all the basic implementations we will
 * require from a general cab,this class will be abstract cause there will be some
 * classes which will derive from this class that we will really use.
 */
class Cab
{
// First public is just for enum defining
public:
	enum cabColor
	{
		RED = 'R', BLUE = 'B', GREEN = 'G', PINK = 'P', WHITE = 'W'
	};
	enum Manufacturer
	{
		HONDA = 'H', SUBARO = 'S', TESLA = 'T', FIAT = 'F'
	};
	enum CabType
	{
		STANDARD = 1, LUXURY = 2
	};

private:
	//For using boost's serialization.
	friend class boost::serialization::access;

	/*
	 * This method will be used during the serialization of this class
	 * with the boost library.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & id;
		ar & numOfKilometers;
		ar & tariff;
		ar & color;
		ar & manufacturer;
	}
protected:
	int id, numOfKilometers, tariff;
	unsigned int movmentAbility;
	char color;
	char manufacturer;
public:
	/*
	 * Default constructor of this class,use delegations to create default values for
	 * private members of this class.
	 */
	Cab() :
			id(0), numOfKilometers(0), tariff(0), movmentAbility(0), color(
					BLUE), manufacturer(HONDA)
	{
	}
	;
	/*
	 * Constructor of this class that will get the cab's id,tariff,color and manufacturer.
	 */
	Cab(int idCab, int tariffCab, char color, char manufacturerCab) :
			id(idCab), tariff(tariffCab), color(color), manufacturer(
					manufacturerCab)
	{
		numOfKilometers = 0;
		movmentAbility = 0;
	}
	;
	//Default destructor of this class.
	virtual ~Cab()
	{
	}
	;
	//Get id of this cab.
	int getCabId() const;
	//Get movement ability of this cab,will depend on the cabType.
	unsigned int getMovmentAbility();
	//Get manufacturer of this cab.
	char getManufacturer() const;
	//Get the kilometers this cab has passed.
	int getKilometerage() const;
	//Get the color of this cab.
	char getColor() const;
	/*
	 * Get the type of this cab:Luxury or Standard,this will be a pure virtual method cause
	 * only the classes that will be derived from this class will care about the type of the
	 * cab.
	 */
	virtual CabType getCabType() = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab);
#endif /* SRC_CAB_H_ */
