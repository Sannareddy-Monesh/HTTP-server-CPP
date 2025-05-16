#pragma once
#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>     
#include <cstring>
#include <cstdlib>
#include <csignal>
#include "Listener.h"
#include "/root/cpp-server/ConnectionsManager/ConnectionsManager.h"

using std::cout;

class Server {

public:
    int serverFd;

    Server(){
        int SocketFd = socket(AF_INET, SOCK_STREAM, 0);

        if (SocketFd < 0) {
            perror("Server creation Failed");
            exit(EXIT_FAILURE);
        } else 
            cout << "Server Created\n";

        this->serverFd = SocketFd;
    }

    void start(const int& PORT, Router* router){

        Listener::listen(serverFd, PORT);
        ConnectionsManager connectionsManager(router);

        while (true){
            connectionsManager.handleConnections(serverFd);
        }
    }
};





