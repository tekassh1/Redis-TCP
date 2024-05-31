#include <string>
#include <vector>
#include <regex>

#include "Commands.h"
#include "CommandManager.h"

using namespace std;

void Count::execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) {
    string res = connection_info->databaseManager->count();
    connection_info->connectionManager->send_command_response(
        connection_info->sock,
        res
    );
};