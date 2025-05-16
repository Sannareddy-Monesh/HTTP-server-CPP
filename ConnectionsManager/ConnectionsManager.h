
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
