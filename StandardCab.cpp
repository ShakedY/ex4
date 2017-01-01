
#include "StandardCab.h"

int StandardCab::getPrice() const
{
	return this->price;
}

Cab::CabType StandardCab::getCabType()
{
	return Cab::STANDARD;
}

void StandardCab::moveOneStep(Point endPoint){
}

template<class Archive>
void StandardCab::serialize(Archive & ar,const unsigned int version) {
	//Serialize base class.
	ar & boost::serialization::base_object<Cab>(*this);
	ar & price;
}
