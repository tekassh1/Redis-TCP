#ifndef DATABASE_MANAGER
#define DATABASE_MANAGER

#include <unordered_map>
#include <string>

using namespace std;

class DatabaseManager {

    unordered_map<string, string> storage;

public:
    string put(string key, string value);
    string get(string key);
    string del(string key);
    string count();
};

#endif