#ifndef UTIL
#define UTIL

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

#endif