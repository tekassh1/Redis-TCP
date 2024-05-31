#include <vector>
#include <unordered_map>
#include <memory>

#include "CommandManager.h"
#include "util.h"

using namespace std;

unordered_map<string, unique_ptr<Command>> CommandManager::command_map;
void CommandManager::init_commands() {
    command_map.emplace("PUT", make_unique<Put>());
    command_map.emplace("GET", make_unique<Get>());
    command_map.emplace("DEL", make_unique<Del>());
    command_map.emplace("COUNT", make_unique<Count>());
}

DWORD WINAPI CommandManager::process_commands(LPVOID lpvoid_pointer) {
    shared_ptr<ConnectionInfo> connection_info((ConnectionInfo*) lpvoid_pointer);

    while (true) {
        string request = read_request(connection_info);
        vector<string> splitted = split(request, ' ');

        if (splitted.empty()) {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "Wrong request format '<command> <key> <value>', you should input at least <command>"
            );
        }
        
        string command_name = splitted[0];
        vector<string> args(splitted.begin() + 1, splitted.end());

        auto it = command_map.find(command_name);
        if (it != command_map.end()) {
            it->second->execute(connection_info, args);
        }
        else {
            connection_info->connectionManager->send_command_response (
                connection_info->sock,
                "Wrong command, availavle commands are GET, PUT, DEL, COUNT."
            );
        }
    }
}

string CommandManager::read_request(shared_ptr<ConnectionInfo> connection_info) {
    int req_size;
    int status1 = recv(connection_info->sock, (char*) &req_size, sizeof(int), NULL);

    if (status1 <= 0) {
        cout << "Connection closed by client." << endl;
        connection_info->connectionManager->discconect_user();
        closesocket(connection_info->sock);
        ExitThread(0);
    }

    char request[req_size + 1];
    request[req_size] = '\0';
    int status2 = recv(connection_info->sock, request, req_size, NULL);

    if (status2 <= 0) {
        cout << "Connection closed by client." << endl;
        connection_info->connectionManager->discconect_user();
        closesocket(connection_info->sock);
        ExitThread(0);
    }

    string command(request);
    return command;
}