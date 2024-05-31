#ifndef CLIENT
#define CLIENT

#include <winsock2.h>
#include <string>

#define LOCALHOST_ADDR "127.0.0.1"
#define BUFFER_SIZE 1024

struct ConnectionStatus {
    bool connected;
    char message[256];
};

class Client {
    int port;
    SOCKET sock;

    std::string read_command();
    std::string process_command(std::string s);
    std::string parse_reponse(char buffer[BUFFER_SIZE]);
public:
    Client(int port);
    void run();

    SOCKET get_socket();
};

#endif