#include <iostream>
#include <minwindef.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <csignal>

#define LOCALHOST_ADDR "127.0.0.1"
#define DEFAULT_PORT 49152

using namespace std;

struct ConnectionStatus {
    bool connected;
    char message[256];
};

SOCKET connection;

void signal_handler(int signal) {
    shutdown(connection, SD_RECEIVE);
    closesocket(connection);
    std::exit(signal);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);

    WSAData wsa_data;
    WORD dll_version = MAKEWORD(2, 2);
    if (WSAStartup(dll_version, &wsa_data) != 0) {
        cout << "Error while client socket declaration." << endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    InetPton(AF_INET, LOCALHOST_ADDR, &addr.sin_addr.s_addr);
    addr.sin_port = htons(DEFAULT_PORT);
    addr.sin_family = AF_INET;

    connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(connection, (SOCKADDR*)& addr, sizeof(addr)) != 0) {
        cout << "Error connecting to server" << endl;
        exit(1);
    }
    
    char buffer[sizeof(ConnectionStatus)];
    recv(connection, buffer, sizeof(ConnectionStatus), 0);
    ConnectionStatus status_struct;
    memcpy(&status_struct, buffer, sizeof(ConnectionStatus));

    if (!status_struct.connected) {
        cout << "Error: " << status_struct.message << endl;
        exit(1);
    }
    cout << "Connection with server established!" << endl;
    
    while (true) {
        string s; cin >> s;
    }

    return 0;
}