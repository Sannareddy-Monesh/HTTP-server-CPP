cmake_minimum_required(VERSION 3.10)
project(CppHttpServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all source files here
add_executable(server
    main.cpp
    Request/Request.cpp
    Response/Response.cpp
    Router/Router.cpp
    ConnectionsManager/ConnectionsManager.cpp
)
