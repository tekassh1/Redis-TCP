#include <iostream>
#include <minwindef.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include "Client.h"

using namespace std;

Client::Client(int port) {
    this->port = port;

    WSAData wsa_data;
    WORD dll_version = MAKEWORD(2, 2);

    if (WSAStartup(dll_version, &wsa_data) != 0) 
        throw runtime_error("Error while client socket declaration.");

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    InetPton(AF_INET, LOCALHOST_ADDR, &addr.sin_addr.s_addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(connection, (SOCKADDR*)& addr, sizeof(addr)) != 0)
        throw runtime_error("Error connecting to server.");
    
    this->sock = connection;

    char buffer[sizeof(ConnectionStatus)];
    recv(connection, buffer, sizeof(ConnectionStatus), 0);
    ConnectionStatus status_struct;
    memcpy(&status_struct, buffer, sizeof(ConnectionStatus));

    if (!status_struct.connected) {
        string recieved(status_struct.message);
        string err_msg = "Error: " + recieved;
        throw runtime_error(err_msg);
    }
    cout << "Success: " << status_struct.message << endl;
}

string Client::read_command() {
    cout << ">>> ";
    string s;
    getline(cin, s);

    if (s.length() == 0) 
        return "";
    if (s.length() > 2048) {
        cout << "Input is too large (Max input size - 2048 symb). Try again." << endl;
        return "";
    }
    return s;
}

string Client::process_command(string s) {
    int command_size = s.size();
    int send_size_status = send(sock, (char*) &command_size, sizeof(int), NULL);
    if (send_size_status <= 0) throw runtime_error("");

    int send_command_status = send(sock, s.c_str(), command_size, NULL);
    if (send_command_status <= 0) throw runtime_error("");

    int resp_size;
    int recieve_size_status = recv(sock, (char*) &resp_size, sizeof(int), NULL);
    if (recieve_size_status <= 0) throw runtime_error("");

    char response[resp_size + 1];
    response[resp_size] = '\0';
    int recieve_reponse_status = recv(sock, response, resp_size, NULL);
    if (recieve_reponse_status <= 0) throw runtime_error("");

    return response;
}

void Client::run() {
    while (true) {
        string command = read_command();
        if (command.empty()) continue;
        string response = process_command(command);
        cout << response << endl;
    }
}