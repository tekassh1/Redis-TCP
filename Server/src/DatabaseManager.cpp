#include "DatabaseManager.h"

using namespace std;

string DatabaseManager::put(string key, string value) {
    unique_lock<shared_mutex> lock(storage_mutex);

    string last = "";
    if (storage.find(key) != storage.end()) last = storage[key];
    storage[key] = value;
    if (last == "") return "OK";
    else return "OK " + last;
}

string DatabaseManager::get(string key) {
    shared_lock<shared_mutex> lock(storage_mutex);

    if (storage.find(key) == storage.end()) return "NE";
    else return "OK " + storage[key];
}

string DatabaseManager::del(string key) {
    unique_lock<shared_mutex> lock(storage_mutex);

    if (storage.find(key) == storage.end()) return "NE";
    string val = storage[key];
    storage.erase(key);
    return "OK " + val;
}

string DatabaseManager::count() {
    shared_lock<shared_mutex> lock(storage_mutex);

    return "OK " + to_string(storage.size());
}