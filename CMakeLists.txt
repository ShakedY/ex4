set(core_SRCS BFSObject.cpp BFSPoint.cpp Cab.cpp CabFactory.cpp Driver.cpp LuxuryCab.cpp Map.cpp Passenger.cpp Point.cpp StandardCab.cpp ClientInput.cpp TaxiCenter.cpp Trip.cpp ClientMainFlow.cpp)

add_library(core ${core_SRCS})
#add_executable(exe main.cpp)

#target_link_libraries(exe core)

