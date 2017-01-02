all:

	g++  src/BFSObject.cpp src/BFSPoint.cpp src/Driver.cpp src/Trip.cpp src/RemoteDriver.cpp src/Cab.cpp src/LuxuryCab.cpp src/StandardCab.cpp src/Passenger.cpp src/ClientInput.cpp src/Client.cpp  src/Map.cpp src/TaxiCenter.cpp src/sockets/Socket.cpp src/sockets/Udp.cpp src/Point.cpp src/CabFactory.cpp -lboost_serialization -o client.out

	g++  src/BFSObject.cpp src/BFSPoint.cpp src/Driver.cpp src/RemoteDriver.cpp src/Cab.cpp src/LuxuryCab.cpp src/StandardCab.cpp src/Passenger.cpp src/Map.cpp src/TaxiCenter.cpp src/sockets/Socket.cpp src/sockets/Udp.cpp src/Point.cpp src/Trip.cpp src/CabFactory.cpp src/Server.cpp src/StringInput.cpp -lboost_serialization -o server.out
