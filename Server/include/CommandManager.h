#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER

#include <winsock2.h>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <gtest/gtest.h>

#include "ConnectionManager.h"
#include "DatabaseManager.h"
#include "Commands.h"

#define BUFFER_SIZE 1024

struct ConnectionInfo {
    ConnectionManager* connectionManager;
    DatabaseManager* databaseManager;
    SOCKET sock;
};

class CommandManager {
    static std::unordered_map<std::string, std::unique_ptr<Command>> command_map;

    FRIEND_TEST(command_manager_tests, init_commands_test);
public:
    static void init_commands();
    static std::string get_commands_string();
    static std::string parse_command(char buffer[BUFFER_SIZE]);
    static void process_commands(std::shared_ptr<ConnectionInfo> connection_info);
    static void send_command_response(SOCKET sock, std::string resp_msg);
};

#endif