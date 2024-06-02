#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <winsock2.h>

std::vector<std::string> split(const std::string& str, char delimiter);
void check_server_args(int argc, char *argv[]);
std::string get_client_ip(SOCKET sock);

#endif