#pragma once

#include "Router.h"
#include <iostream>

// #include "/root/cpp-server/Request/Request.h"
// #include "/root/cpp-server/Response/Response.h"

using std::cout;

Router::Router() {}

void Router::add(const std::string& path, std::function<void(Request*, Response*)> handler) {
    routes[path] = handler;
    cout<< path << " Added Successfully\n";
}

void Router::handle(const std::string& path, Request* req, Response* res)
{
    auto it = routes.find(path);
    std::cout << "Request Path: " << path << "\n";
    std::cout << "\n";

    std::cout << "Available Paths: ";
    for (auto [s, func]: routes){
        std::cout << s << "\n";
    }
    std::cout << "\n";

    if (it != routes.end()) {
        it->second(req, res);
    } else {
        res->statusCode(404);
        res->sendHTML("<h1> File Not Found <h1>");
    }
}
