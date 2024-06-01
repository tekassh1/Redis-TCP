#include <Ws2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <minwindef.h>
#include <thread>

#include <iostream>

#include "ConnectionManager.h"
#include "CommandManager.h"
#include "SerializationManager.h"

using namespace std;

ConnectionManager::ConnectionManager(int port, int max_connections) {
    this->max_connections = max_connections;

    WSAData wsa_data;
    WORD dll_version = MAKEWORD(2, 2);

    if (WSAStartup(dll_version, &wsa_data) != 0)
        throw std::runtime_error("Error while server socket declaration.");

    sizeofaddr = sizeof(addr);
    InetPton(AF_INET, LOCALHOST_ADDR, &addr.sin_addr.s_addr);
    
    int bind_status = -1;
    port--;
    while (bind_status == -1 && ++port <= 65535) {
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;
        s_listen = socket(AF_INET, SOCK_STREAM, NULL);
        bind_status = bind(s_listen, (SOCKADDR*) &addr, sizeof(addr));
    }

    if (bind_status == -1)
        throw std::runtime_error("All ports from 49152 to 65535 are busy. Please, try later.");

    this->port = port;

    connections_am = 0;
    listen(s_listen, SOMAXCONN);
    cout << "The server has successfully launched on port " << "\u001b[38;5;112m" << port << "\u001b[0m" << endl;
}

void ConnectionManager::run() {
    DatabaseManager databaseManager;
    CommandManager::init_commands();
    
    while (true) {
        SOCKET new_connection = accept(s_listen, (SOCKADDR*) &addr, &sizeofaddr);

        if (!validate_connection(new_connection)) continue;

        shared_ptr<ConnectionInfo> connection_info = make_shared<ConnectionInfo>();
        connection_info->connectionManager = this;
        connection_info->databaseManager = &databaseManager;
        connection_info->sock = new_connection;

        if (new_connection == 0) {
            cout << "Client connection error!" << endl;
        }
        else {
            cout << "Client connected!" << endl;
            send_connection_status(new_connection, true, "Connection with server established!");
            connections_am++;
            thread t(CommandManager::process_commands, connection_info);
            t.detach();
        }
    }
}

bool ConnectionManager::validate_connection(SOCKET sock) {
    if (connections_am == max_connections) {
        send_connection_status(sock, false, "Server max amount of connections is reached. Please, try later.");
        closesocket(sock);
        return false;
    }
    return true;
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
    lock_guard<mutex> lock(connection_am_mutex);
    return connections_am;
}

void ConnectionManager::disconnect_user() {
    lock_guard<mutex> lock(connection_am_mutex);
    connections_am--;
}