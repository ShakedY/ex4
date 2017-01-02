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

/*
 * The LuxuryCab class will be derived from the Cab class that we defined before,this
 * cab will move twice as much at each step and will have a higher price.
 */
class LuxuryCab : public Cab
{
private:
	// Use the access for boost serialization.
	friend class boost::serialization::access;

	/*
	 * This method will help us serialize this class by using
	 * the boost library serialization.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//Serialize the base class first.
		ar & boost::serialization::base_object<Cab>(*this);
		ar & price;
	}
protected:
	unsigned int price;
public:

	//Default constructor of this class.
	LuxuryCab() :
		price(0)
	{
		movmentAbility = 2;
	};

	/*
	 * Another constructor of this class that will delegate from constructor of the
	 * Cab class that this class derives from.
	 */
	LuxuryCab(int idCab, Cab::cabColor color, Cab::Manufacturer manufacturerCab) :
		Cab(idCab, 20, color, manufacturerCab), price(1000)
	{
		movmentAbility = 2;
	};

	/*
	 * Another constructor of this class which uses delegations of the constructor of the
	 * Cab class which this class derives from.
	 */
	LuxuryCab(int idCab, int tariffCab, cabColor color,
			Manufacturer manufacturerCab, unsigned int cabPrice) :
			Cab(idCab, tariffCab, color, manufacturerCab), price(
					cabPrice)
	{
		movmentAbility = 2;
	};

	//Get the price of this cab.
	int getPrice() const;

	//Get the type of this cab which is a Luxury Cab.
	Cab::CabType getCabType();
};

#endif /* SRC_LUXURYCAB_H_ */
