#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER

#include <winsock2.h>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "ConnectionManager.h"
#include "DatabaseManager.h"
#include "Commands.h"

using namespace std;

struct ConnectionInfo {
    ConnectionManager* connectionManager;
    DatabaseManager* databaseManager;
    SOCKET sock;
};

class CommandManager {
    static unordered_map<string, unique_ptr<Command>> command_map;
public:
    static void init_commands();
    static DWORD WINAPI process_commands(LPVOID sock_pointer);
    static string read_request(ConnectionInfo* connection_info);
};

#endif