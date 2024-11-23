#include <http_server/alekspress.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

#include "http/request/http_request.hpp"
#include "http/request/request_parser.hpp"

namespace server {
    Alekspress::Alekspress(int port) : _port(std::move(port)), _socket(std::move(_port)) {
    }

    void Alekspress::handle_connections() {
        auto connection = _socket.accept_connection();
        
        http::request::RequestParser parser;
        while (true) {
            const int BUFFER_SIZE = 1024;
            char buffer[BUFFER_SIZE] = {0};
            ssize_t bytes_read = connection.read(buffer, sizeof(buffer));
            // printf("Number of bytes read: %zd\n", bytes_read);
            parser.append_to_request(buffer, bytes_read);
            if (parser.is_request_complete()) {
                break;
            }
        }
        http::request::HttpRequest http_request = http::request::HttpRequest::from_string(parser.complete_request());

        std::cout << "--- HTTP Request Line ---" << std::endl;
        std::cout << http_request.request_line().method() << std::endl;
        std::cout << http_request.request_line().path() << std::endl;
        std::cout << http_request.request_line().http_version() << std::endl;
        std::cout << "--- HTTP Request Headers ---" << std::endl;
        http_request.headers().print_all();
        std::cout << "--- HTTP Request Body ---" << std::endl;
        std::cout << http_request.body().content() << std::endl;
        
        const char* response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, World!";
        connection.write(response, sizeof(response));
    }

    void Alekspress::run() {
        _socket.create();
        _socket.bind();
        _socket.listen();
        printf("Server running on port %d!\n", _port);

        while (true) {
            handle_connections();
        }
    }
}