#include "DatabaseManager.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>

#include "util.h"

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

string DatabaseManager::dump(string filename) {
    shared_lock<shared_mutex> lock(storage_mutex);

    if (filesystem::exists(filename))
        return "This dump filename is already exist.";

    ofstream out_file(filename);

    if (!out_file) return "Error while file processing.";

    auto it = storage.begin();
    while (it != storage.end()) {
        out_file << it->first << "," << it->second << endl;
        it++;
    }

    out_file.close();
    if (out_file.fail()) return "Error while file processing.";

    return "Your database dump successfully saved to a '" + filename + "' file";
}

string DatabaseManager::load(string filename) {
    unique_lock<shared_mutex> lock(storage_mutex);

    if (!filesystem::exists(filename))
        return "This dump filename does not exist.";
    
    ifstream in_file(filename);
    if (!in_file) return "Error while file processing.";

    regex pattern("^[0-9a-zA-Z]+$");

    string line;
    while(getline(in_file, line)) {
        vector<string> splitted = split(line, ',');
        if (splitted.size() < 2)
            return "Error while file parsing. File should only consist of <key>,<value> values separated by a comma.";

        if (!regex_match(splitted[0], pattern))
            return "<key> value in file should contain only digits (0-9) and letters (a-z, A-Z).";
        
        storage[splitted[0]] = splitted[1];
    }

    in_file.close();
    return "Dump from file '" + filename + "' was successfully uploaded. All keys have been overwritten.";
}