#pragma once
#include "network/socket.hpp"

namespace server {
    class Alekspress {
        public:
            Alekspress(int port);

            // Public API for configuring routes
            // void get(const std::string& path, HandlerFunction handler);
            // void post(const std::string& path, HandlerFunction handler);

            // Server lifecycle
            void run(); // Blocking
            // void start(); // Non-blocking
            // void stop();
        
        private:
            int _port;
            void handle_connections();

            // for now
            network::Socket _socket;
    };
}