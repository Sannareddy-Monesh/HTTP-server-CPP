#pragma once

#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>    
#include <cstring>
#include <cstdlib>
using std::cout;

class Listener 
{

public:

    // bind the server socket with addr, port and server starts listening to tcp connections
    static void listen(const int &serverSocketFd, const int &PORT, const in_addr_t address = INADDR_ANY){

        struct sockaddr_in serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        serverAddress.sin_addr.s_addr = address;

        if (bind(serverSocketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
            ::close(serverSocketFd);
            perror("Binding Failed Address, Port with Socket Failed");
            exit(EXIT_FAILURE);
        }

        if (::listen(serverSocketFd, 100) < 0){
            ::close(serverSocketFd);
            perror("listener failed");
            exit(EXIT_FAILURE);
        }

        cout << "Servering is listening on Port: " << PORT << "\n";
    }

};