#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <iostream>
#include <string>
#include <mutex>

#include <gtest/gtest.h>

#define LOCALHOST_ADDR "127.0.0.1"

struct ConnectionStatus {
    bool connected;
    char message[256];
};

class ConnectionManager {
    int port;
    SOCKADDR_IN addr;
    int sizeofaddr;
    SOCKET s_listen;

    int max_connections;
    int connections_am;
    
    std::mutex connection_am_mutex;
    
    FRIEND_TEST(connection_manager_tests, test_connections_limit_not_reached);
    FRIEND_TEST(connection_manager_tests, test_connections_limit_reached);

public:
    ConnectionManager(int port, int max_connections);
    void run();

    bool validate_connection(SOCKET sock);
    int get_connections_am();
    void disconnect_user();
    
    void send_connection_status(SOCKET sock, bool status, std::string s_msg);
};

#endif