#pragma once

#include <string>
// #include <unistd.h>
// #include <fstream>
// #include <sstream>
// #include <sys/socket.h> 

class Response {
private:
    int clientHandle;
    int httpCode;
    std::string statusMessage;
    std::string contentType;
    size_t contentLength;
    std::string body;

    std::string getStatusMessage(int code);

public:
    Response(const int &clientHandle);

    void send(const std::string text);
    void sendHTML(const std::string html);
    void sendHTMLFile(const std::string filePath);
    void statusCode(const int HTTP_CODE);

    void setContentType(const std::string type);
    void setContentLength(const size_t length);

    std::string build();

    void sendResponse(const std::string httpResponse);
    
};
