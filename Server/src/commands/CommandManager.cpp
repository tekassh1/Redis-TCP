#include "CommandManager.h"

DWORD WINAPI CommandManager::process_commands(LPVOID sock_pointer) {
    SOCKET sock = (SOCKET) sock_pointer;
    char msg[256];

    while (true) {
        int status = recv(sock, msg, sizeof(msg), NULL);

        if (status > 0) {
            string message(msg);
            cout << "Client message: " + message << endl; 
        } 
        else if (status == 0) {
            std::cout << "Connection closed by client." << std::endl;
            break;
        } 
        else {
            std::cerr << "Connection error." << WSAGetLastError() << std::endl;
            break;
        }
    }
}