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


class Cab
{
// first public is just for enum defining
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
	friend class boost::serialization::access;

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
	// tariff(Hebrew)
	int id, numOfKilometers, tariff;
	unsigned int movmentAbility;
	char color;
	char manufacturer;
public:
	Cab() :
			id(0), numOfKilometers(0), tariff(0), movmentAbility(0), color(
					BLUE), manufacturer(HONDA)
	{
	}
	;
	Cab(int idCab, int tariffCab, char color, BFSPoint *startLocation,
			char manufacturerCab) :
			id(idCab), tariff(tariffCab), color(color), manufacturer(
					manufacturerCab)
	{
		numOfKilometers = 0;
		movmentAbility = 0;
	}
	;
	virtual ~Cab()
	{
	}
	;

	int getCabId() const;
	unsigned int getMovmentAbility();
	char getManufacturer() const;
	int getKilometerage() const;
	char getColor() const;
	virtual CabType getCabType() = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab);
#endif /* SRC_CAB_H_ */
