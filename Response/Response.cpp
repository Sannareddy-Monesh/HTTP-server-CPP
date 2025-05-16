#pragma once

// #include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h> 
#include <unistd.h>
#include "Response.h"

Response::Response(const int &clientHandle){
    this->clientHandle = clientHandle;
}

std::string Response::getStatusMessage(int code) {
    switch (code) {
        case 200: return "OK";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default:  return "Unknown";
    }
}

void Response::send(const std::string text = "Hello From Server"){
    this->body = text;
    this->setContentType("text/plain");
    this->setContentLength(text.size());
    std::string httpResponse = this->build();
    this->sendResponse(httpResponse);
}

void Response::sendHTML(const std::string html = "<h1> Hellow From Server </h1>"){
    this->body = html;
    this->setContentType("text/html");
    this->setContentLength(html.size());
    std::string httpResponse = this->build();
    this->sendResponse(httpResponse);
}

void Response::sendHTMLFile(const std::string filePath)
{
    std::ifstream htmlFile(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!htmlFile.is_open()) {
        perror("Failed to open HTML file");
        exit(EXIT_FAILURE);
    }

    std::streamsize size = htmlFile.tellg();
    htmlFile.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    if (!htmlFile.read(buffer, size)) {
        perror("Failed to read file");
        exit(EXIT_FAILURE);
    }

    sendHTML(std::string(buffer, size));
}

void Response::sendResponse(const std::string httpResponse){
    ssize_t sent_length = ::send(clientHandle, httpResponse.c_str(), httpResponse.size(), 0);

    if (sent_length < 0){
        perror("Failed to send data to Client");
        ::close(clientHandle);
        delete (this);
    }
}

void Response::setContentType(const std::string type) {
    this->contentType = type;
}

void Response::setContentLength(const size_t length) {
    this->contentLength = length;
}

void Response::statusCode(const int HTTP_CODE){
    this->httpCode = HTTP_CODE;
    this->statusMessage = getStatusMessage(HTTP_CODE);
}

std::string Response::build() {
    std::ostringstream response;

    response << "HTTP/1.1 " << httpCode << " " << statusMessage << "\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << contentLength << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << this->body;

    return response.str();
}