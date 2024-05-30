#ifndef CLIENT
#define CLIENT

#include <winsock2.h>
#include <string>

#define LOCALHOST_ADDR "127.0.0.1"

using namespace std;

struct ConnectionStatus {
    bool connected;
    char message[256];
};

class Client {
    int port;
    SOCKET sock;

    string read_command();
    string process_command(string s);

public:
    Client(int port);
    void run();

    SOCKET get_socket();
};

#endif