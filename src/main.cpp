#include <iostream>
#include "server.h"

int main() {
    std::cout << "Redis-CPP Server Starting..." << std::endl;

    // Create and start the Redis server
    Server server(6379);
    
    if (!server.start()) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }
    
    // Run the server (this will block)
    server.run();
    
    std::cout << "Server shutting down..." << std::endl;
    return 0;
}