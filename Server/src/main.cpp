#include <iostream>

#include <minwindef.h>
#include <stdexcept>
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <vector>

#include "ConnectionManager.h"
#include "LoggingManager.h"
#include "util.h"

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

vector<SOCKET> connections;

int main(int argc, char *argv[]) {

    check_server_args(argc, argv);
    LoggingManager::init();

    try {
        ConnectionManager connection_manager(stoi(argv[1]), stoi(argv[2]));
        connection_manager.run();
    }
    catch (runtime_error const& connection_manager_exception) {
        spdlog::critical(connection_manager_exception.what());
        exit(1);
    }

    return 0;
}