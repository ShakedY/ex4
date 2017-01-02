a.out: 
	g++ src/BFSObject.cpp src/BFSPoint.cpp src/Cab.cpp src/CabFactory.cpp src/Driver.cpp src/LuxuryCab.cpp src/ClientMainFlow.cpp src/Map.cpp src/Passenger.cpp src/Point.cpp src/StandardCab.cpp src/ClientInput.cpp src/TaxiCenter.cpp src/Trip.cpp -lboost_serialization -o a.out
	

