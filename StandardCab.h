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

/*
 * The StandardCab will derive from the Cab class,it will move only one step each time
 * and it's price will be lower than the LuxuryCab's price.
 */
class StandardCab: public Cab
{
private:
	unsigned int price;
	//Use for boost serialization.
	friend class boost::serialization::access;

	/*
	 * This function will run when we use boost's library serialization.
	 */
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		//Serialize base class.
		ar & boost::serialization::base_object<Cab>(*this);
		ar & price;
	}
public:
	//Default constructor.
	StandardCab() :
			price(0)
	{
		movmentAbility = 1;
	};

	/*
	 * Constructor which gets same parameters as the Cab's constructor so it \
	 * uses from it.
	 */
	StandardCab(int idCab, Cab::cabColor color, Cab::Manufacturer manufacturerCab) :
			Cab(idCab, 10, color, manufacturerCab), price(500)
	{
		movmentAbility = 1;
	};

	/*
	 * Another constructor which gets same parameters as the Cab's constructor,only difference
	 * is assigning 1 to movementAbility which indicates this is a StandardCab.
	 */
	StandardCab(int idCab, int tariffCab, cabColor color, Manufacturer manufacturerCab,
			unsigned int cabPrice) :
			Cab(idCab, tariffCab, color, manufacturerCab), price(cabPrice)
	{
		movmentAbility = 1;
	}
	;

	//Get the price of the cab.
	int getPrice() const;

	//Get the type of the cab.
	Cab::CabType getCabType();
};
#endif /* SRC_STANDARDCAB_H_ */
