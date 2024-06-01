#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "CommandManager.h" 

TEST(command_manager_tests, parse_command_lf) {
    char buffer[BUFFER_SIZE];

    std::string input_message = "This is a test command\n";
    strncpy(buffer, input_message.c_str(), BUFFER_SIZE);

    CommandManager command_manager;

    std::string expected_message = "This is a test command";
    std::string result_message = command_manager.parse_command(buffer);

    ASSERT_EQ(result_message, expected_message);
}

TEST(command_manager_tests, parse_command_crlf) {
    char buffer[BUFFER_SIZE];

    std::string input_message = "This is a test command\r\n";
    strncpy(buffer, input_message.c_str(), BUFFER_SIZE);

    CommandManager command_manager;

    std::string expected_message = "This is a test command";
    std::string result_message = command_manager.parse_command(buffer);

    ASSERT_EQ(result_message, expected_message);
}

TEST(command_manager_tests, parse_empty_command) {
    char buffer[BUFFER_SIZE] = {0};

    CommandManager command_manager;

    std::string expected_message = "";
    std::string result_message = command_manager.parse_command(buffer);

    ASSERT_EQ(result_message, expected_message);
}

TEST(command_manager_tests, parse_overflow_command_lf) {
    char buffer[BUFFER_SIZE];

    std::string input_message = "This is a test command\naaaaaaa";
    strncpy(buffer, input_message.c_str(), BUFFER_SIZE);

    CommandManager command_manager;

    std::string expected_message = "This is a test command";
    std::string result_message = command_manager.parse_command(buffer);

    ASSERT_EQ(result_message, expected_message);
}

TEST(command_manager_tests, parse_overflow_command_crlf) {
    char buffer[BUFFER_SIZE];

    std::string input_message = "This is a test command\r\naaaaaa";
    strncpy(buffer, input_message.c_str(), BUFFER_SIZE);

    CommandManager command_manager;

    std::string expected_message = "This is a test command";
    std::string result_message = command_manager.parse_command(buffer);

    ASSERT_EQ(result_message, expected_message);
}

TEST(command_manager_tests, init_commands_test) {
    int expected = 6;
    std::vector<std::string> command_list = {"PUT", "GET", "DEL", "COUNT", "DUMP", "LOAD"};

    CommandManager command_manager;
    command_manager.init_commands();

    ASSERT_EQ(command_manager.command_map.size(), expected);
    for (const auto& command : command_list) {
        EXPECT_NE(command_manager.command_map.find(command), command_manager.command_map.end());
    }
}