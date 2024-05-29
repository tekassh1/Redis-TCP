#include <iostream>
#include <minwindef.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#define LOCALHOST_ADDR "127.0.0.1"
#define DEFAULT_PORT 49152

using namespace std;

int main(int argc, char *argv[]) {
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

    SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(connection, (SOCKADDR*)& addr, sizeof(addr)) != 0) {
        cout << "Error connecting to server" << endl;
        exit(1);
    }
    cout << "Connection with server established!" << endl;

    char msg[256];
    recv(connection, msg, sizeof(msg), NULL);
    cout << msg << endl;

    return 0;
}