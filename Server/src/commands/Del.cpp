#include <string>
#include <vector>
#include <regex>

#include "Commands.h"
#include "CommandManager.h"

using namespace std;

void Del::execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) {
    if (args.size() < 1) {
        string msg =  "You should pass <key> argument for DEL command.";
        CommandManager::send_command_response(connection_info->sock, msg);
        return;
    }

    regex pattern("^[0-9a-zA-Z]+$");
    if (!regex_match(args[0], pattern)) {
        string msg = "<key> arg should contain only digits (0-9) and letters (a-z, A-Z).";
        CommandManager::send_command_response(connection_info->sock, msg);
        return;
    }

    string res = connection_info->databaseManager->del(args[0]);
    CommandManager::send_command_response(connection_info->sock, res);
}