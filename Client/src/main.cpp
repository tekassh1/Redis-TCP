#include <iostream>
#include <minwindef.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <csignal>

#include "Client.h"

#define LOCALHOST_ADDR "127.0.0.1"
#define DEFAULT_PORT 49152

using namespace std;

SOCKET connection;

void signal_handler(int signal) {
    shutdown(connection, SD_RECEIVE);
    closesocket(connection);
    std::exit(signal);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    int port;

    if (argc < 2) {
        throw invalid_argument("To run client you should pass <port> argument.");
    }
    try {
        port = stoi(argv[1]);
    }
    catch (invalid_argument const& int_excpetion) {
        throw invalid_argument("Port should be numeric value.");
    }
    if (port < 49152 || port > 65535) 
        throw invalid_argument("Available ports range is from 49152 to 65535. Connections range is from 1 to 1000.");

    try {
        Client client(port);
        connection = client.get_socket();
        client.run();
    } catch(const runtime_error& e) {
        cerr << "Server is unavailable now. Please, try later." << endl;
        exit(1);
    }

    return 0;
}