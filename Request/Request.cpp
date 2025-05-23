
#pragma once

// #include <string>
#include <iostream>
// #include <unordered_map>
#include <sstream>
#include "Request.h"

void Request::parse(char* buffer, ssize_t bytes){
    // parse the request and store it in properties
    std::string raw_request(buffer, bytes);

    std::istringstream stream(raw_request);
    std::string line;

    std::string method, path, protocol;

    // Parse Request
    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        lineStream >> method >> path >> protocol;
    }

    this->setMethod(method);
    this->setPath(path);
    this->setProtocol(protocol);

    // 2. Parse Headers
    while (std::getline(stream, line)) {
        if (line == "\r" || line.empty()) break; // End of headers

        size_t colon = line.find(':');
        if (colon != std::string::npos) {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 1);

            // Trim spaces and carriage returns
            key.erase(key.find_last_not_of(" \r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of("\r\n") + 1);

            if (key == "Host") this->setHost(value);
            else headers[key] = value;
        }
    }
}

std::string Request::getMethod(){
    return this->method;
}

std::string Request::getPath(){
    return this->path;
}

std::string Request::getHost(){
    return this->host;
}

std::string Request::getIP(){
    return this->ip;
}    

std::string Request::getProtocol(){
    return this->protocol;
}

void Request::setMethod(std::string method){
    this->method = method;
}

void Request::setPath(std::string path){
    this->path = path;
}

void Request::setHost(std::string host){
    this->host = host;
}

void Request::setIP(std::string ip){
    this->ip = ip;
}    

void Request::setProtocol(std::string protocol){
    this->protocol = protocol;
}