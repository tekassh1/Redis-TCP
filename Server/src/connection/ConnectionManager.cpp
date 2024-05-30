#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>

#include <iostream>

#include "ConnectionManager.h"
#include "CommandManager.h"
#include "SerializationManager.h"

using namespace std;

ConnectionManager::ConnectionManager(int port, int max_connections) {
    this->port = port;
    this->max_connections = max_connections;

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

    connections_am = 0;
    listen(s_listen, SOMAXCONN);
}

void ConnectionManager::run() {

    while (true) {
        SOCKET new_connection = accept(s_listen, (SOCKADDR*) &addr, &sizeofaddr);

        if (connections_am == max_connections) {
            send_connection_status(new_connection, false, "Server max amount of connections is reached. Please, try later.");
            closesocket(new_connection);
            continue;
        }

        ConnectionInfo* connection_info = new ConnectionInfo;
        connection_info->connectionManager = this;
        connection_info->sock = new_connection;

        if (new_connection == 0) {
            cout << "Client connection error!" << endl;
        }
        else {
            cout << "Client connected!" << endl;
            send_connection_status(new_connection, true, "Connection with server established!");
            connections_am++;
            CreateThread(NULL, 0, CommandManager::process_commands, (LPVOID) (connection_info), NULL, NULL);
        }
    }
}

void ConnectionManager::send_connection_status(SOCKET sock, bool status, string s_msg) {

    ConnectionStatus status_struct = {
        .connected = status
    };
    strncpy(status_struct.message, s_msg.c_str(), s_msg.length());
    status_struct.message[sizeof(status_struct.message) - 1] = '\0';

    char buffer[sizeof(ConnectionStatus)];
    SerializationManager::SerializeResponse(status_struct, buffer);

    send(sock, buffer, sizeof(ConnectionStatus), NULL);
}

int ConnectionManager::get_connections_am() {
    return connections_am;
}

void ConnectionManager::discconect() {
    connections_am--;
}