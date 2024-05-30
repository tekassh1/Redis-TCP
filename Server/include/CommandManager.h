#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER

#include <winsock2.h>
#include <iostream>
#include <string>

#include "ConnectionManager.h"

using namespace std;

struct ConnectionInfo {
    ConnectionManager* connectionManager;
    SOCKET sock;
};

struct Command {
    int code;
    string arg;
};

class CommandManager {

public:
    static DWORD WINAPI process_commands(LPVOID sock_pointer);
    static string read_request(ConnectionInfo* connection_info);
};

#endif