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
        cout << err_msg << endl;
        exit(1);
    }
    cout << "\u001b[38;5;112m" << "Success: " << "\u001b[0m" << status_struct.message << endl 
         << "Enter command, or \'exit\' to disconnect." << "\n\n";
}

string Client::read_command() {
    cout << "\u001b[38;5;112m" << ">>> " << "\u001b[0m";
    string s;
    getline(cin, s);

    if (s.length() == 0) 
        return "";
    if (s.length() > 2048) {
        cout << "Input is too large (Max input size - 2048 symb). Try again." << endl;
        return "";
    }
    if (s == "exit") exit(1);

    return s;
}

string Client::process_command(string s) {
    s += "\n";
    int send_command_status = send(sock, s.c_str(), s.length(), NULL);
    if (send_command_status <= 0) throw runtime_error("");

    char buffer[BUFFER_SIZE];
    int recieve_reponse_status = recv(sock, buffer, BUFFER_SIZE, NULL);
    if (recieve_reponse_status <= 0) throw runtime_error("");

    string response = parse_reponse(buffer);
    if (response.empty()) {
        cout << "Server error. Wrong command format. String should end with 'LF' or 'CR LF'.";
        exit(1);
    }
    return response;
}

string Client::parse_reponse(char buffer[BUFFER_SIZE]) {
    string message;

    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == '\n' || (buffer[i] == '\r' && (i + 1 < BUFFER_SIZE) && buffer[i + 1] == '\n')) {
            message = string(buffer, i);
            break;
        }
    }
    return message;
}

void Client::run() {
    while (true) {
        string command = read_command();
        if (command.empty()) continue;
        string response = process_command(command);
        cout << response << endl << endl;
    }
}

SOCKET Client::get_socket() {
    return sock;
}