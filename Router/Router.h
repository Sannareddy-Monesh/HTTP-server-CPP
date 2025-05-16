#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include "/root/cpp-server/Request/Request.h"
#include "/root/cpp-server/Response/Response.h"


class Request;
class Response;

class Router{
    
private:
    std::unordered_map<std::string, std::function<void(Request* req, Response* res)>> routes;

public:
    Router();

    void add(const std::string &path, std::function<void(Request* req, Response* res)> handler);

    void handle(const std::string& path, Request* req, Response* res);
    
};
