/*
 * StandardCab.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_STANDARDCAB_H_
#define SRC_STANDARDCAB_H_
#include "Cab.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

class StandardCab: public Cab
{
private:
	unsigned int price;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		//Serialize base class.
		ar & boost::serialization::base_object<Cab>(*this);
		ar & price;
	}
public:
	StandardCab() :
			price(0)
	{
		movmentAbility = 1;
	}
	;

	StandardCab(int idCab, Cab::cabColor color, Cab::Manufacturer manufacturerCab) :
			Cab(idCab, 10, color, manufacturerCab), price(500)
	{
		movmentAbility = 1;
	}
	;

	StandardCab(int idCab, int tariffCab, cabColor color, Manufacturer manufacturerCab,
			unsigned int cabPrice) :
			Cab(idCab, tariffCab, color, manufacturerCab), price(cabPrice)
	{
		movmentAbility = 1;
	}
	;

	int getPrice() const;
	Cab::CabType getCabType();
};
#endif /* SRC_STANDARDCAB_H_ */
