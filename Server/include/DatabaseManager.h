#ifndef DATABASE_MANAGER
#define DATABASE_MANAGER

#include <unordered_map>
#include <string>
#include <mutex>
#include <shared_mutex>

class DatabaseManager {
    std::unordered_map<std::string, std::string> storage;
    std::shared_mutex storage_mutex;
public:
    std::string put(std::string key, std::string value);
    std::string get(std::string key);
    std::string del(std::string key);
    std::string count();
    
    std::string dump(std::string filename);
    std::string load(std::string filename);
};

#endif