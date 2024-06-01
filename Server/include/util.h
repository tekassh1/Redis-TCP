#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter);
void check_server_args(int argc, char *argv[]);

#endif