#pragma once

#include "connection.hpp"

namespace network {
    class Socket {
        public:
            Socket(int port);
            ~Socket();

            // Rule of five
            // Prevent copying
            Socket(const Socket&) = delete; // Can't copy construct
            Socket& operator=(const Socket&) = delete; // Can't copy assign
            // Allow moving
            Socket(Socket&&) = default; // Can move construct
            Socket& operator=(Socket&&) = default; // Can move assign

            void create();
            void bind();
            void listen();
            Connection accept_connection() const;

            int file_descriptor() const { return _sockfd; }
        
        private:
            int _sockfd;
            int _port;
            static constexpr int CLIENT_TIMEOUT_SECONDS = 5;
    };
}