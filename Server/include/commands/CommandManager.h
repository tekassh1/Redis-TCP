#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER

#include <winsock2.h>
#include <iostream>

#include "ConnectionManager.h"

using namespace std;

struct ConnectionInfo {
    ConnectionManager* connectionManager;
    SOCKET sock;
};

class CommandManager {

public:
    static DWORD WINAPI process_commands(LPVOID sock_pointer);
};

#endif