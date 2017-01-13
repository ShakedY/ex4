#include "Server.h"
#include <stdlib.h>
#define BUFFSIZE 1024
volatile int running_threads = 0;

Server::Server(int argc, char* argv[]) :
		factory()
{
	//Create Udp socket.Port will be in command line arguments.
	socket = new Tcp(1, atoi(argv[1]));
	socket->initialize();
	StringInput input(argc, argv);
	input.readMapInfo();
	createMap(input);
	mainLoop(input);
}

Server::~Server()
{
	delete center;
	delete map;
}

Cab* Server::createCab(StringInput::CabInfo cabsInfo)
{
	//Create a cab with the CabFactory object.
	return factory.generateCab(cabsInfo.id, cabsInfo.taxi_type, cabsInfo.color,
			cabsInfo.manufacturer);
}

Trip* Server::createTrip(StringInput::TripInfo tripInfo)
{
	//Create a new trip based on the TripInfo.
	Point start(tripInfo.x_start, tripInfo.y_start), end(tripInfo.x_end,
			tripInfo.y_end);
	return new Trip(tripInfo.id, tripInfo.num_passengers, start, end,
			tripInfo.tariff, tripInfo.time);
}

void Server::createMap(StringInput& info)
{
	//Create a new map based on the info entered in StringInfo.
	map = new Map(info.gridInfo.width, info.gridInfo.height,
			*(info.gridInfo.obstacles));
}

void Server::mainLoop(StringInput& info)
{
	//Create our TaxiCenter.
	center = TaxiCenter::getInstance(map);
	int answer, driver_id;
	const Point* location;
	Trip *tmp;
	do
	{
		scanf("%d", &answer);
		switch (answer)
		{
			case 1:
				//Get number of drivers from the user.
				getNumDrivers();
				break;
			case 2:
				//Case 2,get Trip from the console and add it to the TaxiCenter.
				info.getTripInfo();
				tmp = createTrip(info.tripInfo);
				center->addTrip(tmp);
				break;
			case 3:
				//Case 3,get Cab from the console and add it to the TaxiCenter.
				info.getCabInfo();
				center->addCab(createCab(info.cabInfo));
				break;
			case 4:
				//Case 4,get id of driver and print it's location.
				scanf("%d", &driver_id);
				location = center->getDriverLocation(driver_id);
				if (location != NULL) {
					cout << *location << endl;
				}
				break;
			case 9:
				//Tell the TaxiCenter to move all the drivers by one step.
				center->moveAllOneStep();
				break;
			default:
				// no such option
				break;
		}
	} while (answer != 7);
	//Send shutdown to all the clients.
	center->endWorking();
}

void Server::getNumDrivers()
{
	int numDrivers, size;
	char buffer[BUFFSIZE];
	Tcp* clientSocket;
	RemoteDriver* currentDriver;
	Driver *drv;
	pthread_t currentThread;
	int thread;
	pthread_mutex_t currentLock;
	Param* currentStruct;
	//Scan the number of drivers from the console.
	scanf("%d", &numDrivers);
	running_threads = numDrivers;
	//Now we expect to get the drivers through the socket and send them cabs.
	while (numDrivers-- != 0)
	{

		// Deserialize the data.
		//Move accept of client to a thread so we will be able to get clients at once.
		currentStruct = new Param;
		currentStruct->serverSocket = socket;
		//Set up the mutex lock.
		pthread_mutex_init(&(currentStruct->locker),0);
		//Create thread for running the code blocking accept.
		thread = pthread_create(&currentThread,NULL,Server::manageClient
							,currentStruct);
	}
	//Wait for all the threads to end by sleeping.
	while (running_threads > 0) {
		sleep(1);
	}
	center->attachCabsToDrivers();
	// sending the clients trips
	center->attachDriversToTrips();
}

void* Server::manageClient(void * params) {
	Param* parameters = (Param*) params;
	Socket* mySocket = parameters->serverSocket;
	pthread_mutex_t lock = parameters->locker;
	Tcp* clientSocket;
	Driver* drv;
	TaxiCenter* myCenter = TaxiCenter::getInstance();
	int size;
	char buffer[BUFFSIZE];
	RemoteDriver* currentDriver;
	//Get descriptor of client.
	clientSocket = ((Tcp*)mySocket)->acceptClient();
	size = clientSocket->reciveData(buffer, BUFFSIZE);
	drv = Server::deSerializeObj<Driver>(buffer, size);
	//Create the new remote driver.
	currentDriver = new RemoteDriver(drv, clientSocket);
	//Remote driver saved all of the driver's data so delete the driver.
	delete drv;
	//Add the RemoteDriver to the TaxiCenter.
	//We will lock before adding to prevent severe cases.
	pthread_mutex_lock(&lock);
	//Decrease the number of threads to know we got the client.
	running_threads--;
	myCenter->addDriver(currentDriver);
	pthread_mutex_unlock(&lock);
	//Destroy the mutex lock.
	pthread_mutex_destroy(&lock);

}

template<class T>
void Server::serializeObj(std::string* serial_str, T* obj)
{
	//Serialize an object same as recitations examples.
	boost::iostreams::back_insert_device<std::string> inserter(*serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
			inserter);
	boost::archive::binary_oarchive oa(s);
	oa << obj;
	s.flush();
}

template<class T>
T* Server::deSerializeObj(const char* serial_str, int size)
{
	//Deserialize an object same as recitations examples.
	T* obj;
	boost::iostreams::basic_array_source<char> device(serial_str, size);
	boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
			device);
	boost::archive::binary_iarchive ia(s);
	ia >> obj;
	return obj;
}

int main(int argc, char* argv[])
{
	Server flow(argc, argv);
	return 0;
}
