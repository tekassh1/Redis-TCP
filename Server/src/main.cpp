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
    int max_conn_am;

    try {
        if (argc < 3) {
            throw invalid_argument("To run server you should pass arguments <port> <max_available_connections>");
        }
        try {
            port = stoi(argv[1]);
            max_conn_am = stoi(argv[2]);
        }
        catch (invalid_argument const& int_excpetion) {
            throw invalid_argument("Port and connections amount should be numeric value.");
        }
        if (port < 49152 || port > 65535) 
            throw invalid_argument("Available ports range is from 49152 to 65535. Connections range is from 1 to 1000.");
    }
    catch (invalid_argument const& port_exception) {
        cout << "Error: " << port_exception.what() <<endl;
        exit(1);
    }

    try {
        ConnectionManager connection_manager(port, max_conn_am);
        connection_manager.run();
    }
    catch (runtime_error const& connection_manager_exception) {
        cout << "Error: " << connection_manager_exception.what() <<endl;
        exit(1);
    }

    return 0;
}