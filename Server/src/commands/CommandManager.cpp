#include "CommandManager.h"

DWORD WINAPI CommandManager::process_commands(LPVOID lpvoid_pointer) {
    ConnectionInfo* connection_info = (ConnectionInfo*) lpvoid_pointer;

    char msg[256];
    
    while (true) {
        int status = recv(connection_info->sock, msg, sizeof(msg), NULL);

        if (status > 0) {
            string message(msg);
            cout << "Client message: " + message << endl; 
        }
        else if (status == 0) {
            cout << "Connection closed by client." << endl;
        
            connection_info->connectionManager->discconect();
            closesocket(connection_info->sock);
            
            delete connection_info;
            ExitThread(0);
        }
        else {
            connection_info->connectionManager->discconect();
            closesocket(connection_info->sock);

            delete connection_info;
            ExitThread(0);
        }
    }
}