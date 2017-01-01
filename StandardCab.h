/*
 * StandardCab.h
 *
 *  Created on: Dec 3, 2016
 *      Author: assaf
 */

#ifndef SRC_STANDARDCAB_H_
#define SRC_STANDARDCAB_H_
#include "Cab.h"

class StandardCab : public Cab
{
private:
	unsigned int price;
	friend	class boost::serialization::access;
public:
	StandardCab() :
			price(0)
	{
		movmentAbility = 1;
	}
	;

	StandardCab(int idCab, Cab::cabColor color, Cab::Manufacturer manufacturerCab) :
			Cab(idCab, 10, color, new BFSPoint(0,0), manufacturerCab), price(500)
	{
		movmentAbility = 1;
	}
	;

	StandardCab(int idCab, int tariffCab, cabColor color,
			BFSPoint *startLocation, Manufacturer manufacturerCab,
			unsigned int cabPrice) :
			Cab(idCab, tariffCab, color, startLocation, manufacturerCab), price(
					cabPrice)
	{
		movmentAbility = 1;
	}
	;

	int getPrice() const;
	Cab::CabType getCabType();
	template<class Archive>
	void serialize(Archive & ar,unsigned int version);
	void moveOneStep(Point endPoint);
};
#endif /* SRC_STANDARDCAB_H_ */
