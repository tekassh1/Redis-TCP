#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "DatabaseManager.h"

class DatabaseManagerTest : public ::testing::Test {
protected:
    DatabaseManager db;

    void SetUp() override {}

    void TearDown() override {
        db.get_storage()->clear();
    }
};

class DatabaseManagerDumpTest : public ::testing::Test {
protected:
    DatabaseManager db;

    void SetUp() override {
        db.put("key1", "value1");
        db.put("key2", "value2");
    }

    void TearDown() override {
        db.del("key1");
        db.del("key2");
    }
};

class DatabaseManagerLoadTest : public ::testing::Test {
protected:
    DatabaseManager db;

    void SetUp() override {
        std::ofstream outfile("test_dump.txt");
        outfile << "key1,value1\n";
        outfile << "key2,value2\n";
        outfile.close();
    }

    void TearDown() override {
        std::filesystem::remove("test_dump.txt");
    }
};

TEST_F(DatabaseManagerTest, put_new_key_test) {
    std::string result = db.put("key1", "value1");
    ASSERT_EQ(result, "OK");
}

TEST_F(DatabaseManagerTest, put_existing_key_test) {
    db.put("key1", "value1");
    std::string result = db.put("key1", "value2");
    ASSERT_EQ(result, "OK value1");
}

TEST_F(DatabaseManagerTest, get_existing_key_test) {
    db.put("key1", "value1");
    std::string result = db.get("key1");
    ASSERT_EQ(result, "OK value1");
}

TEST_F(DatabaseManagerTest, get_non_existing_key_test) {
    std::string result = db.get("key1");
    ASSERT_EQ(result, "NE");
}

TEST_F(DatabaseManagerTest, delete_existing_key_test) {
    db.put("key1", "value1");
    std::string result = db.del("key1");
    ASSERT_EQ(result, "OK value1");
}

TEST_F(DatabaseManagerTest, delete_non_existing_key_test) {
    std::string result = db.del("key1");
    ASSERT_EQ(result, "NE");
}

TEST_F(DatabaseManagerTest, count_keys_test) {
    db.put("key1", "value1");
    db.put("key2", "value2");
    std::string result = db.count();
    ASSERT_EQ(result, "OK 2");
}

TEST_F(DatabaseManagerDumpTest, dump_success_test) {
    std::string filename = "test_dump.txt";
    std::string result = db.dump(filename);

    std::unordered_map<std::string, std::string> copied_map;
    for (const auto& pair : *(db.get_storage())) {
        copied_map[pair.first] = pair.second;
    }
    db.get_storage()->clear();
    db.load(filename);

    ASSERT_EQ(result, "Your database dump successfully saved to a '" + filename + "' file");
    ASSERT_TRUE(std::filesystem::exists(filename));
    ASSERT_EQ(copied_map.size(), db.get_storage()->size());

    for (const auto& pair : copied_map) {
        const auto& key = pair.first;
        const auto& value = pair.second;

        ASSERT_TRUE(db.get_storage()->count(key) > 0);
        ASSERT_EQ(value, (*db.get_storage())[key]);
    }

    std::filesystem::remove(filename);
}

TEST_F(DatabaseManagerDumpTest, dump_file_already_exists_test) {
    std::string filename = "test_dump.txt";
    std::ofstream outfile(filename);
    outfile.close();

    std::string result = db.dump(filename);
    ASSERT_EQ(result, "This dump filename is already exist.");

    std::filesystem::remove(filename);
}

TEST_F(DatabaseManagerDumpTest, dump_file_error_test) {
    std::string filename = "/root/test_dump.txt";
    std::string result = db.dump(filename);
    ASSERT_EQ(result, "Error while file processing.");
}

TEST_F(DatabaseManagerLoadTest, load_success_test) {
    std::string result = db.load("test_dump.txt");
    ASSERT_EQ(result, "Dump from file 'test_dump.txt' was successfully uploaded. All keys have been overwritten.");

    ASSERT_EQ(db.get("key1"), "OK value1");
    ASSERT_EQ(db.get("key2"), "OK value2");
}

TEST_F(DatabaseManagerLoadTest, load_file_not_exist_test) {
    std::string result = db.load("non_existing_file.txt");
    ASSERT_EQ(result, "This dump filename does not exist.");
}

TEST_F(DatabaseManagerLoadTest, load_key_pattern_match_test) {
    std::ofstream outfile("test_dump.txt");
    outfile << "1../23,key_value\n";
    outfile.close();

    std::string result = db.load("test_dump.txt");
    ASSERT_EQ(result, "<key> value in file should contain only digits (0-9) and letters (a-z, A-Z).");
}

TEST_F(DatabaseManagerLoadTest, load_line_format_error) {
    std::ofstream outfile("test_dump.txt");
    outfile << "key_value\n";
    outfile.close();

    std::string result = db.load("test_dump.txt");
    ASSERT_EQ(result, "Error while file parsing. File should only consist of <key>,<value> values separated by a comma.");
}