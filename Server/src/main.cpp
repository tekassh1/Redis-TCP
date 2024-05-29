#include <iostream>

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <vector>
#include <string>

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

vector<SOCKET> connections;

int main(int argc, char *argv[]) {

    int port;
    
    try {
        if (argc < 2) throw invalid_argument("To run server you should pass listening port argument.");
        try {
            port = stoi(argv[1]);
        }
        catch (invalid_argument const& int_excpetion) {
            throw invalid_argument("Port should be numeric value.");
        }
        if (port < 49152 || port > 65535) throw invalid_argument("Available ports range is from 49152 to 65535.");
    }
    catch (invalid_argument const& port_exception) {
        cout<<"Error: " << port_exception.what() <<endl;
        exit(1);
    }
    
    WSAData wsa_data;
    WORD dll_version = MAKEWORD(2, 2);
    if (WSAStartup(dll_version, &wsa_data) != 0) {
        cout << "Error while server socket declaration." << endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    InetPton(AF_INET, LOCALHOST_ADDR, &addr.sin_addr.s_addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    SOCKET s_listen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(s_listen, (SOCKADDR*) &addr, sizeof(addr));
    listen(s_listen, SOMAXCONN);

    SOCKET new_connection;
    while (true) {
        new_connection = accept(s_listen, (SOCKADDR*) &addr, &sizeofaddr);

        if (new_connection == 0) {
            cout << "Client connection error!" << endl;
        }
        else {
            cout << "Client connected successfully!" << endl;
            char msg[256] = "Hello, my client!";
            send(new_connection, msg, sizeof(msg), NULL);
        }
    }

    return 0;
}