#include <string>
#include <vector>
#include <regex>

#include "Commands.h"
#include "CommandManager.h"

using namespace std;

void Put::execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) {
    
    if (args.size() < 2) {
        string msg =  "You should pass <key> <value> arguments for PUT command.";
        CommandManager::send_command_response(connection_info->sock, msg);
        return;
    }

    regex pattern("^[0-9a-zA-Z]+$");
    if (!regex_match(args[0], pattern)) {
        string msg = "<key> arg should contain only digits (0-9) and letters (a-z, A-Z).";
        CommandManager::send_command_response(connection_info->sock, msg);
        return;
    }

    string res = connection_info->databaseManager->put(args[0], args[1]);
    CommandManager::send_command_response(connection_info->sock, res);
}