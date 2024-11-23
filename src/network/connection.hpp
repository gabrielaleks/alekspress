#pragma once
#include <string>
#include <netinet/in.h>

namespace network {
    class Connection {
        public:
            ~Connection();

            // Rule of five
            // Prevent copying
            Connection(const Connection&) = delete; // Can't copy construct
            Connection& operator=(const Connection&) = delete; // Can't copy assign
            // Allow moving
            Connection(Connection&&) = default; // Can move construct
            Connection& operator=(Connection&&) = default; // Can move assign

            std::string ip() const;
            int port() const;

            ssize_t read(char* buffer, size_t size);
            void write(const char* data, size_t size);
        private:
            Connection(int client_socket, sockaddr_in client_address);
            friend class Socket;
            
            int _client_socket;
            sockaddr_in _client_address;
    };
}