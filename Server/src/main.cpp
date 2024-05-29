#include <iostream>

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <vector>
#include <string>

#include "ConnectionManager.h"

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

vector<SOCKET> connections;

int main(int argc, char *argv[]) {

    int port;
    
    try {
        if (argc < 2) 
            throw invalid_argument("To run server you should pass listening port argument.");
        try {
            port = stoi(argv[1]);
        }
        catch (invalid_argument const& int_excpetion) {
            throw invalid_argument("Port should be numeric value.");
        }
        if (port < 49152 || port > 65535) 
            throw invalid_argument("Available ports range is from 49152 to 65535.");
    }
    catch (invalid_argument const& port_exception) {
        cout << "Error: " << port_exception.what() <<endl;
        exit(1);
    }

    try {
        ConnectionManager connection_manager(port);
        connection_manager.run();
    }
    catch (runtime_error const& connection_manager_exception) {
        cout << "Error: " << connection_manager_exception.what() <<endl;
        exit(1);
    }

    return 0;
}