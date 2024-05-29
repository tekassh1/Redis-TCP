#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <iostream>

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

class ConnectionManager {
    int port;
    SOCKADDR_IN addr;
    int sizeofaddr;
    SOCKET s_listen;

public:
    ConnectionManager(int port);
    void run();
};

#endif