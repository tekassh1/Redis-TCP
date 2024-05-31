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
    command_map.emplace("DUMP", make_unique<Dump>());
    command_map.emplace("LOAD", make_unique<Load>());
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

        char buffer[BUFFER_SIZE];
        int status = recv(connection_info->sock, buffer, BUFFER_SIZE, NULL);

        if (status <= 0) {
            cout << "Connection closed by client." << endl;
            connection_info->connectionManager->discconect_user();
            closesocket(connection_info->sock);
            ExitThread(0);
        }

        string command = parse_command(buffer);
        if (command.empty()) {
            string msg = "Wrong command format. String should end with 'LF' or 'CR LF'.";
            send_command_response(connection_info->sock, msg);
        }

        vector<string> splitted = split(command, ' ');

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
    resp_msg += "\n";
    send(sock, resp_msg.c_str(), resp_msg.length(), NULL);
}

string CommandManager::parse_command(char buffer[BUFFER_SIZE]) {
    string message;

    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == '\n' || (buffer[i] == '\r' && (i + 1 < BUFFER_SIZE) && buffer[i + 1] == '\n')) {
            message = string(buffer, i);
            break;
        }
    }
    return message;
}