#include <vector>

#include "CommandManager.h"
#include "util.h"

DWORD WINAPI CommandManager::process_commands(LPVOID lpvoid_pointer) {
    ConnectionInfo* connection_info = (ConnectionInfo*) lpvoid_pointer;
    
    while (true) {
        string request = read_request(connection_info);
        vector<string> splitted = split(request, ' ');

        if (splitted.size() < 1) {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "Wrong request format '<command> <key> <value>', you should input at least <command>"
            );
        }
        
        string command = splitted[0];
        if (command == "PUT") {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "You asked PUT command"
            );
        }
        else if (command == "GET") {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "You asked GET command"
            );
        }
        else if (command == "DEL") {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "You asked DEL command"
            );
        }
        else if (command == "COUNT") {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "You asked COUNT command"
            );
        }
        else {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "Wrong command, availavle commands are GET, PUT, DEL, COUNT."
            );
        }
    }
}

string CommandManager::read_request(ConnectionInfo* connection_info) {
    int req_size;
    int status1 = recv(connection_info->sock, (char*) &req_size, sizeof(int), NULL);

    if (status1 <= 0) {
        cout << "Connection closed by client." << endl;
        connection_info->connectionManager->discconect_user();
        closesocket(connection_info->sock);
        delete connection_info;
        ExitThread(0);
    }

    char request[req_size + 1];
    request[req_size] = '\0';
    int status2 = recv(connection_info->sock, request, req_size, NULL);

    if (status2 <= 0) {
        cout << "Connection closed by client." << endl;
        connection_info->connectionManager->discconect_user();
        closesocket(connection_info->sock);
        delete connection_info;
        ExitThread(0);
    }

    string command(request);
    return command;
}