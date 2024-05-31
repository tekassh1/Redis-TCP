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

string CommandManager::get_commands_string() {
    string res = "";
    auto it = command_map.begin();
    while (it != command_map.end()) {
        if (next(it) == command_map.end()) res += it->first;
        else res += it->first + ", ";
        it++;
    }
    return res;
}

void CommandManager::process_commands(shared_ptr<ConnectionInfo> connection_info) {
    while (true) {
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
        vector<string> splitted = split(request, ' ');

        if (splitted.empty()) {
            string msg = "Wrong request format '<command> <key> <value>', you should input at least <command>";
            send_command_response(connection_info->sock, msg);
        }

        string command_name = splitted[0];
        vector<string> args(splitted.begin() + 1, splitted.end());

        auto it = command_map.find(command_name);
        if (it != command_map.end()) {
            it->second->execute(connection_info, args);
        }
        else {
            string msg = "Wrong command, availavle commands are " + get_commands_string() + ".";
            send_command_response(connection_info->sock, msg);
        }
    }
}

void CommandManager::send_command_response(SOCKET sock, string resp_msg) {
    int response_size = resp_msg.size();
    send(sock, (char*) &response_size, sizeof(int), NULL);
    send(sock, resp_msg.c_str(), response_size, NULL);
}