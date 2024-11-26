#include <http_server/alekspress.hpp>
#include <http_server/request.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

#include "http/request/request.hpp"
#include "http/response/response.hpp"
#include "http/response/status_line.hpp"
#include "http/response/headers.hpp"
#include "http/response/body.hpp"
#include "http/request/request_parser.hpp"

namespace alekspress {
    Alekspress::Alekspress(int port) : _port(std::move(port)), _socket(std::move(_port)) {
    }

    void Alekspress::get(const std::string& path, HandlerFunction handler) {
        _handlers[path]["GET"] = handler;
    }

    void Alekspress::post(const std::string& path, HandlerFunction handler) {
        _handlers[path]["POST"] = handler;
    }

    void Alekspress::put(const std::string& path, HandlerFunction handler) {
        _handlers[path]["PUT"] = handler;
    }

    void Alekspress::patch(const std::string& path, HandlerFunction handler) {
        _handlers[path]["PATCH"] = handler;
    }

    void Alekspress::del(const std::string& path, HandlerFunction handler) {
        _handlers[path]["DELETE"] = handler;
    }

    void Alekspress::handle_connections() {
        auto connection = _socket.accept_connection();
        
        internal::request::RequestParser parser;
        while (true) {
            const int BUFFER_SIZE = 1024;
            char buffer[BUFFER_SIZE] = {0};
            ssize_t bytes_read = connection.read(buffer, sizeof(buffer));
            parser.append_to_request(buffer, bytes_read);
            if (parser.is_request_complete()) {
                break;
            }
        }
        auto raw_request = RawRequest::from_string(parser.complete_request());

        // FROM raw request TO user request
        UserRequest user_request = UserRequest::from_raw_request(raw_request);

        HandlerFunction handler = _handlers[user_request.path()][user_request.method()];

        // Execute handler with user request, generating user response
        UserResponse user_response = handler(user_request);
        
        // FROM user response TO raw response
        RawResponse raw_response = RawResponse::from_user_response(user_response);

        // Serialize raw response and write it
        std::string raw_response_serialized = raw_response.serialize();
        connection.write(raw_response_serialized.c_str(), raw_response_serialized.length());
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