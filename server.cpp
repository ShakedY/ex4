#include <iostream>
#include "src/sockets/Udp.h"
#include <unistd.h>

int main() {
    std::cout << "Hello, from server" << std::endl;

    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");


//
//    usleep(5000);
    Udp udp2(1, 5554);
    udp2.initialize();

    char buffer2[1024];
    udp2.reciveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2.sendData("sup?");

    // support more than one client?
    return 0;
}