#include <iostream>
#include "Server/Server.h"
#include "Router/Router.h"

using std::cout;

int main(){

    Server* server = new Server();
    Router* router = new Router();

    router->add("/api", [](Request *req, Response *res) -> void {
        res->statusCode(200);
        res->sendHTMLFile("/root/cpp-server/Static/index.html");
    });

    server->start(8080, router);

    delete server;
    delete router;
    return 0;
}
