#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <iostream>

#include "ConnectionManager.h"

using namespace std;

ConnectionManager::ConnectionManager(int port) {
    this->port = port;

    WSAData wsa_data;
    WORD dll_version = MAKEWORD(2, 2);

    if (WSAStartup(dll_version, &wsa_data) != 0)
        throw std::runtime_error("Error while server socket declaration.");

    sizeofaddr = sizeof(addr);
    InetPton(AF_INET, LOCALHOST_ADDR, &addr.sin_addr.s_addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    s_listen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(s_listen, (SOCKADDR*) &addr, sizeof(addr));

    listen(s_listen, SOMAXCONN);
}

void ConnectionManager::run() {
    SOCKET new_connection;
    int cntr = 0;

    while (true) {
        cntr++;
        new_connection = accept(s_listen, (SOCKADDR*) &addr, &sizeofaddr);

        if (new_connection == 0) {
            cout << "Client connection error!" << endl;
        }
        else {
            cout << "Client connected successfully!" << endl;
            char msg[256] = "Hello, my client!";
            send(new_connection, msg, sizeof(msg), NULL);
        }
        cout << "Client " << cntr << " connected" << endl;
    }
}