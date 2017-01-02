/*
 * LuxuryCab.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_LUXURYCAB_H_
#define SRC_LUXURYCAB_H_
#include "Cab.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

class LuxuryCab : public Cab
{
private:
	// friends
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Cab>(*this);
		ar & price;
	}
protected:
	unsigned int price;
public:
	LuxuryCab() :
		price(0)
	{
		movmentAbility = 2;
	}
	;
	LuxuryCab(int idCab, Cab::cabColor color, Cab::Manufacturer manufacturerCab) :
		Cab(idCab, 20, color, manufacturerCab), price(1000)
	{
		movmentAbility = 2;
	}
	;
	LuxuryCab(int idCab, int tariffCab, cabColor color,
			Manufacturer manufacturerCab, unsigned int cabPrice) :
			Cab(idCab, tariffCab, color, manufacturerCab), price(
					cabPrice)
	{
		movmentAbility = 2;
	}
	;

	int getPrice() const;
	Cab::CabType getCabType();
};

#endif /* SRC_LUXURYCAB_H_ */
