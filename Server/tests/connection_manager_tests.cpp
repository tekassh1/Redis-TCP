#include <gtest/gtest.h>
#include <winsock2.h>

#include "ConnectionManager.h"

bool isSocketOpen(SOCKET sockfd) {
    if (sockfd == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }
    closesocket(sockfd);
    WSACleanup();
    return true;
}

bool isSocketClosed(SOCKET sockfd) {
    if (sockfd == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }
    
    closesocket(sockfd);
    WSACleanup();

    char buffer[1];
    int result = recv(sockfd, buffer, sizeof(buffer), 0);
    if (result == 0 || (result == SOCKET_ERROR && WSAGetLastError() == WSAENOTSOCK)) {
        return true;
    }
    return false;
}

TEST(connection_manager_tests, test_connections_limit_not_reached) {
    int max_connections = 5;
    
    ConnectionManager connection_manager(49152, max_connections);
    connection_manager.connections_am = max_connections - 1;
    
    WSADATA wsaData;
    ASSERT_EQ(WSAStartup(MAKEWORD(2, 2), &wsaData), 0);

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ASSERT_NE(sockfd, INVALID_SOCKET);

    ASSERT_TRUE(connection_manager.validate_connection(sockfd));
    ASSERT_TRUE(isSocketOpen(sockfd));

    closesocket(sockfd);
    WSACleanup();
}

TEST(connection_manager_tests, test_connections_limit_reached) {
    int max_connections = 5;

    ConnectionManager connection_manager(49152, max_connections);
    connection_manager.connections_am = max_connections;
    
    WSADATA wsaData;
    ASSERT_EQ(WSAStartup(MAKEWORD(2, 2), &wsaData), 0);

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ASSERT_NE(sockfd, INVALID_SOCKET);

    ASSERT_FALSE(connection_manager.validate_connection(sockfd));
    ASSERT_TRUE(isSocketClosed(sockfd));

    closesocket(sockfd);
    WSACleanup();
}

TEST(connection_manager_tests, test_disconnect_user) {

    ConnectionManager connection_manager(49152, 5);
    connection_manager.disconnect_user();
    connection_manager.disconnect_user();
    connection_manager.disconnect_user();
    int initial_connections = connection_manager.get_connections_am();

    connection_manager.disconnect_user();

    ASSERT_EQ(connection_manager.get_connections_am(), initial_connections - 1);
}