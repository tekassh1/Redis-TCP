#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER

#include <winsock2.h>
#include <iostream>

using namespace std;

class CommandManager {
    
public:
    static DWORD WINAPI process_commands(LPVOID sock_pointer);
};

#endif