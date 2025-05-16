# 🚀 Custom C++ HTTP Server

A lightweight **HTTP/1.1 server** built from scratch in modern C++ using POSIX sockets.  
Displayed how to build a simple web server with core HTTP features, request parsing, routing, and response handling — no external dependencies.

---

## ✨ Features

- 🖧 TCP socket server that accepts client connections  
- 📄 Parses HTTP requests: method, path, protocol, headers  
- 🛣️ Custom routing system to register URL endpoints with handler functions  
- 📤 Generates HTTP responses with status codes, headers, and body (plain text or HTML)  
- 📂 Serves static HTML files  
- 📝 Logs client IP addresses and handles errors gracefully

---

## 🚀 Getting Started

### 🛠️ Prerequisites

- 🐧 Linux or macOS environment (POSIX-compliant)  
- 🧑‍💻 C++ compiler with C++17 support (e.g., g++, clang++)  
- 📦 CMake 3.10 or higher

### ⚙️ Build & Run

```bash
git clone https://github.com/yourusername/cpp-http-server.git
cd cpp-http-server
mkdir build && cd build
cmake ..
make
./CppHttpServer
