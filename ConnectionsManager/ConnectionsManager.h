// #pragma once

// #include <iostream>
// #include <sys/socket.h> 
// #include <netinet/in.h> 
// #include <arpa/inet.h>  
// #include <unistd.h>     
// #include <cstring>
// #include <cstdlib>
// #include "/root/cpp-server/Request/Request.h" 
// #include "/root/cpp-server/Response/Response.h"
// #include "/root/cpp-server/Router/Router.h"
// using namespace std;



// class ConnectionsManager {
// private:
//     Router* router;
// public:

//     ConnectionsManager(Router* router){
//         this->router = router;
//     }

//     // accept the connection from backlog pool and returns client socket FD
//     int acceptConnection(int serverSocketFd, Request* req){
//         struct sockaddr_in clientAddress;
//         socklen_t clientAddrlen = sizeof(clientAddress);

//         int clientHandle = accept(serverSocketFd, (struct sockaddr *)&clientAddress, &clientAddrlen);

//         if (clientHandle < 0)
//         {
//             ::close(serverSocketFd);
//             perror("Failed to accept client connection");
//             exit(EXIT_FAILURE);
//         }

//         // client details like IP and Port
//         char clientIP[INET_ADDRSTRLEN];
//         inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);

//         cout << "Accepted connection from client IP: " << clientIP << ", Port: " << ntohs(clientAddress.sin_port) << "\n";

//         req->setIP(std::string(clientIP));
//         return clientHandle;
//     }

//     void receiveRequestFromClient(int clientHandle, Request* req, const int &serverSocket){
//         char buffer[1024 * 1024] = {0}; // to store data recived from client

//         ssize_t bytesRecived = recv(clientHandle, buffer, sizeof(buffer), 0);

//         if (bytesRecived < 0)
//         {
//             ::close(serverSocket);
//             ::close(clientHandle);
//             perror("Failed to receive data from Client");
//             exit(EXIT_FAILURE);
//         }else {
//             cout << "buffer: " << string(buffer, bytesRecived) << endl;
//         }
        
//         req->parse(buffer, bytesRecived);
//     }

    
//     void handleConnections(const int &serverSocket){

//         Request* req = new Request();

//         int clientHandle = acceptConnection(serverSocket, req); 
//         receiveRequestFromClient(clientHandle, req, serverSocket);

//         Response* res = new Response(clientHandle);
    
//         router->handle(req->getPath(), req, res);

//         cout << "Server sent HTTP response successfully to client\n";
//         ::close(clientHandle);
//     }
// };

#pragma once

#include <iostream>
#include "/root/cpp-server/Router/Router.h"
#include "/root/cpp-server/Request/Request.h"
#include "/root/cpp-server/Response/Response.h"

// Forward declarations
class Request;
class Router;
class Response;

class ConnectionsManager {
private:
    Router* router;

public:
    ConnectionsManager(Router* router);

    int acceptConnection(int serverSocketFd, Request* req);

    void receiveRequestFromClient(int clientHandle, Request* req, const int& serverSocket);

    void handleConnections(const int& serverSocket);
};
