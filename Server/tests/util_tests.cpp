#include <gtest/gtest.h>
#include <stdexcept>
#include "util.h"

TEST(util_server_args_tests, test_less_args)
{
	int argc1 = 0;
    int argc2 = 1;
    int argc3 = 2;
    
    ASSERT_EXIT(check_server_args(argc1, nullptr), ::testing::ExitedWithCode(1), "");
    ASSERT_EXIT(check_server_args(argc2, nullptr), ::testing::ExitedWithCode(1), "");
    ASSERT_EXIT(check_server_args(argc3, nullptr), ::testing::ExitedWithCode(1), "");
}

TEST(util_server_args_tests, test_non_digit_input)
{
    int argc = 3;
    char* argv1[] = {"program_name", "abcde", "1234"};
    char* argv2[] = {"program_name", "1234", "abcde"};

    ASSERT_EXIT(check_server_args(argc, argv1), ::testing::ExitedWithCode(1), "");
    ASSERT_EXIT(check_server_args(argc, argv2), ::testing::ExitedWithCode(1), "");
}

TEST(util_server_args_tests, test_ivalid_port_range)
{
    int argc = 3;
    char* argv1[] = {"program_name", "49151", "5"};
    char* argv2[] = {"program_name", "65536", "5"};

    ASSERT_EXIT(check_server_args(argc, argv1), ::testing::ExitedWithCode(1), "");
    ASSERT_EXIT(check_server_args(argc, argv2), ::testing::ExitedWithCode(1), "");
}

TEST(util_server_args_tests, test_correct_data)
{
    int argc = 3;
    char* argv1[] = {"program_name", "49152", "1"};
    char* argv2[] = {"program_name", "65535", "5"};
    char* argv3[] = {"program_name", "55555", "15"};

    ASSERT_NO_FATAL_FAILURE(check_server_args(argc, argv1));
    ASSERT_NO_FATAL_FAILURE(check_server_args(argc, argv2));
    ASSERT_NO_FATAL_FAILURE(check_server_args(argc, argv3));
}

TEST(util_split_tests, basic_split) {
    std::string input = "apple,orange,banana";
    char delimiter = ',';
    std::vector<std::string> expected = {"apple", "orange", "banana"};

    auto result = split(input, delimiter);

    ASSERT_EQ(result, expected);
}

TEST(util_split_tests, empty_string_split) {
    std::string input = "";
    char delimiter = ',';
    std::vector<std::string> expected = {};

    auto result = split(input, delimiter);

    ASSERT_EQ(result, expected);
}

TEST(util_split_tests, no_delimiter_split) {
    std::string input = "hello";
    char delimiter = ',';
    std::vector<std::string> expected = {"hello"};

    auto result = split(input, delimiter);

    ASSERT_EQ(result, expected);
}