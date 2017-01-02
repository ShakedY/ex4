#include "StandardCab.h"


int StandardCab::getPrice() const
{
	return this->price;
}

Cab::CabType StandardCab::getCabType()
{
	return Cab::STANDARD;
}

BOOST_CLASS_EXPORT(StandardCab);
