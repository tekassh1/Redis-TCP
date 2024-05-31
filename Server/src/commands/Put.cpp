#include <string>
#include <vector>
#include <regex>

#include "Commands.h"
#include "CommandManager.h"

using namespace std;

void Put::execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) {
    if (args.size() < 2) {
        connection_info->connectionManager->send_command_response(
            connection_info->sock,
            "You should pass <key> <value> arguments for PUT command."
        );
    }

    regex pattern("^[0-9a-zA-Z]+$");
    if (!regex_match(args[0], pattern)) {
        connection_info->connectionManager->send_command_response(
            connection_info->sock,
            "<key> arg should contain only digits (0-9) and letters (a-z, A-Z)."
        );
    }

    string res = connection_info->databaseManager->put(args[0], args[1]);
    connection_info->connectionManager->send_command_response(
        connection_info->sock,
        res
    );
}