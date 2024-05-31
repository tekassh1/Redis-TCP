#include "DatabaseManager.h"

using namespace std;

string DatabaseManager::put(string key, string value) {
    string last = "";
    if (storage.find(key) != storage.end()) last = storage[key];
    storage[key] = value;
    if (last == "") return "OK";
    else return "OK " + last;
}

string DatabaseManager::get(string key) {
    if (storage.find(key) == storage.end()) return "NE";
    else return "OK " + storage[key];
}

string DatabaseManager::del(string key) {
    if (storage.find(key) == storage.end()) return "NE";
    string val = storage[key];
    storage.erase(key);
    return "OK " + val;
}

string DatabaseManager::count() {
    return "OK " + to_string(storage.size());
}