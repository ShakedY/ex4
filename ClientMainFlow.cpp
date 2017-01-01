#include "ClientMainFlow.h"
#include <stdlib.h>
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

using namespace std;
using namespace boost::archive;

ClientMainFlow::ClientMainFlow(int argc, char* argv[]){
	ClientInput input(argc, argv);
	mainLoop(input);
}

ClientMainFlow::~ClientMainFlow(){
}

Driver* ClientMainFlow::createDriver(ClientInput::DriverInfo driverInfo){
	return new Driver(driverInfo.id, driverInfo.age, driverInfo.stat,
			driverInfo.yearsOfExperience,NULL,NULL);
}

void ClientMainFlow::mainLoop(ClientInput& info)
{
	int answer, driver_id;
	
	//-------------------------get driver's members as input---------------
	info.getDriverInfo();
	Driver * newDriver = createDriver(info.driverInfo);

	Driver d = *newDriver;

	//---------------------------serializing the driver--------------------
	std::string serial_str;
   	boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s	(inserter);
    	boost::archive::binary_oarchive oa(s);
    	oa << d;
    	s.flush();

	cout << "printing serialization.." << endl;
    	cout << serial_str << endl;

	//-----------------------------deserialization------------------------
	/*
	cout << "now deserialize" << endl;
    	boost::iostreams::basic_array_source<char> device(serial_str.c_str(), 		serial_str.size());
    	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2	(device);
    	boost::archive::binary_iarchive ia(s2);
    	ia >> d;

    	cout << d.getId() << " " << d.getAge() << " " << d.getExperience() << endl;*/
	
	
}

void ClientMainFlow::printMenu()
{
	cout << "Insert driver (id,age,status,experience,vehicle_id) " << endl;
}

int main(int argc, char* argv[])
{
	ClientMainFlow flow(argc, argv);
	return 0;
}
