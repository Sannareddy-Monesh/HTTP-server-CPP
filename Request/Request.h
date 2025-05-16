#pragma once

#include <string>
#include <unordered_map>
// #include <sstream>


class Request {
private:
    std::string method;
    std::string path;
    std::string host;
    std::string ip;
    std::string protocol;

    std::unordered_map<std::string, std::string> headers;

public:
    void parse(char* buffer, ssize_t bytes);
    
    std::string getMethod();

    std::string getPath();

    std::string getHost();

    std::string getIP();

    std::string getProtocol();

    void setMethod(std::string method);

    void setPath(std::string path);

    void setHost(std::string host);

    void setIP(std::string ip);

    void setProtocol(std::string protocol);
};