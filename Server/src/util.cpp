#include "util.h"
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void check_server_args(int argc, char *argv[]) {
    try {
        int port;
        int max_conn_am;
        
        if (argc < 3) {
            throw std::invalid_argument("To run server you should pass arguments <port> <max_available_connections>");
        }
        try {
            port = std::stoi(argv[1]);
            max_conn_am = std::stoi(argv[2]);
        }
        catch (std::invalid_argument const& int_excpetion) {
            throw std::invalid_argument("Port and connections amount should be numeric value.");
        }
        if (port < 49152 || port > 65535) 
            throw std::invalid_argument("Available ports range is from 49152 to 65535. Connections range is from 1 to 1000.");
    }
    catch (std::invalid_argument const& port_exception) {
        std::cout << "Error: " << port_exception.what() << std::endl;
        exit(1);
    }
}

std::string get_client_ip(SOCKET sock) {
    sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    return std::string(client_ip);
}