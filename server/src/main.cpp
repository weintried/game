#include <iostream>
using std::cout;

#include "server.hpp"

int main() {
    cout << "Starting server..." << std::endl;

    Server server;
    server.start();
    // ...existing code...
    server.stop();
    return 0;
}