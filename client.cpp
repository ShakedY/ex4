//
// Created by yanaiela on 12/10/16.
//

#include "src/sockets/Udp.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello");
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;
}
