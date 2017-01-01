
#include "LuxuryCab.h"
#include "Cab.h"


int LuxuryCab::getPrice() const
{
	return this->price;
}

Cab::CabType LuxuryCab::getCabType()
{
	return Cab::LUXURY;
}

BOOST_CLASS_EXPORT(LuxuryCab);
