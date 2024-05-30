#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <iostream>
#include <string>

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

struct Response {
    int status_code;
    string message;
};

class ConnectionManager {
    int port;
    SOCKADDR_IN addr;
    int sizeofaddr;
    SOCKET s_listen;

    int max_connections;
    int connections_am;

public:
    ConnectionManager(int port, int max_connections);
    void run();

    int get_connections_am();
    void new_connection();
    void discconect();
};

#endif