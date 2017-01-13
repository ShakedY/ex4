#ifndef CLIENT_MAINFLOW_H_
#define CLIENT

#include <string>
#include "CabFactory.h"
#include "TaxiCenter.h"
#include "Map.h"
#include "sockets/Tcp.h"
#include "sockets/Socket.h"

class Map;
class CabFactory;
class TaxiCenter;
class ClientInput;
/*
 * This is our Client class,it is used as one side of the communication process
 * between the client and the server in our program.The Client will create a driver according
 * to the input that it got from the user,send it to the server and then get a cab and afterwards
 * a trip from the server,it will shutDown when the server will tell him to do so.
 */
class Client
{
private:
	//Socket that would be used as one side of the communication process.
	Socket* mySocket;
	//The driver this client will represent.
	Driver* driver;
	//This driver's cab(will be given from sever).
	Cab* cab;
	//The client's Trip,will be given from server as wll.
	Trip* trip;
public:
	/*
	 * Define an enum named Actions that will be used as commands that will be sent between
	 * the Client and the Server during their communication process.
	 */
	typedef enum
	{
		moveOneStep = 0, setTrip = 1, endedTrip = 2, shutDown = 3
	} Actions;
	/*
	 * Constructor of the Client class,will get the command line arguments which we will get in
	 * the main function,using these arguments it will create a socket with the entered
	 * ip adress and port.
	 */
	Client(int argc, char* argv[]);
	/*
	 * Destructor of client class.
	 */
	virtual ~Client();
	/*
	 * This method will get an input from the user and create the driver accordingly,afterwards
	 * it will serialize the driver and send it to the server and then wait for the server's
	 * response which will be the cab for this driver,this function starts the communication
	 * with the server and runs until it ends.
	 */
	void buildDriver();
	/*
	 * This function will get the serialized trip from the server,deserialize it and set
	 * it to be the trip which the driver this Client represents will hold.
	 */
	void getTripFromServer();
	/*
	 * This function will run a switch of commands from the Actions enum and will run a
	 * different operation according to the Action the Server will send to this Client.
	 */
	void run();
	/*
	 * This serialize function will get an adress of a string and a pointer to some class
	 * which we defined with a template and will serialize it with boost's serialization and
	 * write the serialized string to the entered adress.
	 */
	template<class T>
	void serializeObj(std::string* serial_str, T* obj);
	/*
	 * This function will get a pointer to a char array and it's size and will deserialize it
	 * with boost's serialization library and return a pointer to the deserialized object,because
	 * we want the function to be generic and deserialize a lot of classes we used a template.
	 */
	template<class T>
	T* deSerializeObj(const char* serial_str, int size);
};

#endif /* CLIENT	*/
