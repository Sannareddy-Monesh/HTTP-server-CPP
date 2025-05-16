
#include "ConnectionsManager.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

ConnectionsManager::ConnectionsManager(Router* router) {
    this->router = router;
}

int ConnectionsManager::acceptConnection(int serverSocketFd, Request* req) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddrlen = sizeof(clientAddress);

    int clientHandle = accept(serverSocketFd, (struct sockaddr*)&clientAddress, &clientAddrlen);

    if (clientHandle < 0) {
        ::close(serverSocketFd);
        perror("Failed to accept client connection");
        exit(EXIT_FAILURE);
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);

    std::cout << "Accepted connection from client IP: " << clientIP
              << ", Port: " << ntohs(clientAddress.sin_port) << "\n";

    req->setIP(std::string(clientIP));
    return clientHandle;
}

void ConnectionsManager::receiveRequestFromClient(int clientHandle, Request* req, const int& serverSocket) {
    char buffer[1024 * 1024] = {0}; // 1MB buffer

    ssize_t bytesReceived = recv(clientHandle, buffer, sizeof(buffer), 0);

    if (bytesReceived < 0) {
        ::close(serverSocket);
        ::close(clientHandle);
        perror("Failed to receive data from Client");
        exit(EXIT_FAILURE);
    } else {
        std::cout << "buffer: " << std::string(buffer, bytesReceived) << std::endl;
    }

    req->parse(buffer, bytesReceived);
}

void ConnectionsManager::handleConnections(const int& serverSocket) {
    Request* req = new Request();
    int clientHandle = acceptConnection(serverSocket, req);
    receiveRequestFromClient(clientHandle, req, serverSocket);

    Response* res = new Response(clientHandle);
    router->handle(req->getPath(), req, res);

    std::cout << "Server sent HTTP response successfully to client\n";
    ::close(clientHandle);

    delete req;
    delete res;
}
