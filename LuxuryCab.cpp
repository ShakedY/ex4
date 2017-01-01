
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

void LuxuryCab::moveOneStep(Point endPoint){
}

template<class Archive>
void LuxuryCab::serialize(Archive & ar,const unsigned int version) {
	//Serialize base class.
	ar & boost::serialization::base_object<Cab>(*this);
	ar & price;
}
