all:

	g++  src/bfs/BFSObject.cpp src/bfs/BFSPoint.cpp src/drivers/Driver.cpp src/map/Trip.cpp src/drivers/RemoteDriver.cpp src/cabs/Cab.cpp src/cabs/LuxuryCab.cpp src/cabs/StandardCab.cpp src/map/Passenger.cpp src/client/ClientInput.cpp src/client/Client.cpp  src/map/Map.cpp src/server/TaxiCenter.cpp src/sockets/Socket.cpp src/sockets/Tcp.cpp src/bfs/Point.cpp src/cabs/CabFactory.cpp src/threads/GlobalInfo.cpp src/threads/TripsCalcThread.cpp -pthread -lboost_serialization -o client.out

	g++  src/bfs/BFSObject.cpp src/bfs/BFSPoint.cpp src/drivers/Driver.cpp src/drivers/RemoteDriver.cpp src/cabs/Cab.cpp src/cabs/LuxuryCab.cpp src/cabs/StandardCab.cpp src/map/Passenger.cpp src/map/Map.cpp src/server/TaxiCenter.cpp src/sockets/Socket.cpp src/sockets/Tcp.cpp src/bfs/Point.cpp src/map/Trip.cpp src/cabs/CabFactory.cpp src/server/Server.cpp src/server/StringInput.cpp src/threads/GlobalInfo.cpp src/threads/TripsCalcThread.cpp -lboost_serialization -pthread -o server.out
