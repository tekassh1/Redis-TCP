#include <iostream>
#include <minwindef.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <csignal>

#include "Client.h"

#define LOCALHOST_ADDR "127.0.0.1"
#define DEFAULT_PORT 49152

using namespace std;

// void signal_handler(int signal) {
//     shutdown(connection, SD_RECEIVE);
//     closesocket(connection);
//     std::exit(signal);
// }

int main(int argc, char *argv[]) {
    // signal(SIGINT, signal_handler);

    int port = 49152;
    
    try {
        Client client(port);
        client.run();
    } catch(const runtime_error& e) {
        cerr << "Server is unavailable now. Please, try later." << endl;
        exit(1);
    }

    return 0;
}