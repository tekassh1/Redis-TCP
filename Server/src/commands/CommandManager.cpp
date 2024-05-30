#include "CommandManager.h"

DWORD WINAPI CommandManager::process_commands(LPVOID lpvoid_pointer) {
    ConnectionInfo* connection_info = (ConnectionInfo*) lpvoid_pointer;
    
    while (true) {
        int req_size;
        int status1 = recv(connection_info->sock, (char*) &req_size, sizeof(int), NULL);

        if (status1 <= 0) {
            cout << "Connection closed by client." << endl;
            connection_info->connectionManager->discconect();
            closesocket(connection_info->sock);
            delete connection_info;
            ExitThread(0);
        }

        char request[req_size + 1];
        request[req_size] = '\0';
        int status2 = recv(connection_info->sock, request, req_size, NULL);

        if (status2 <= 0) {
            cout << "Connection closed by client." << endl;
            connection_info->connectionManager->discconect();
            closesocket(connection_info->sock);
            delete connection_info;
            ExitThread(0);
        }

        string message(request);
        cout << "Client message: " + message << endl; 
    }
}