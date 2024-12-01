#pragma once

#include "network/socket.hpp"
#include "http/request/request_parser.hpp"
#include "route/route.hpp"
#include <alekspress/request.hpp>
#include <alekspress/response.hpp>
#include <functional>
#include <unordered_map>

namespace alekspress {
    using HandlerFunction = std::function<Response(const Request&)>;
    using Parser = internal::request::RequestParser;
    using RawRequest = internal::request::Request;
    using RawResponse = internal::response::Response;
    using UserRequest = alekspress::Request;
    using UserResponse = alekspress::Response;

    class Alekspress {
        public:
            Alekspress(int port);

            // Public API for configuring routes
            void get(const std::string& path, HandlerFunction handler);
            void post(const std::string& path, HandlerFunction handler);
            void put(const std::string& path, HandlerFunction handler);
            void patch(const std::string& path, HandlerFunction handler);
            void del(const std::string& path, HandlerFunction handler);
            void options(const std::string& path, HandlerFunction handler);
            void head(const std::string& path, HandlerFunction handler);

            // Server lifecycle
            void run(); // Blocking
            // void start(); // Non-blocking
            // void stop();
        
        private:
            int _port;
            void handle_connections();

            struct RouteHandler {
                internal::Route route;
                HandlerFunction handler;
            };
            
            std::unordered_map<
                std::string,               // method
                std::vector<RouteHandler>  // list of routes and handlers
            > _handlers;

            std::pair<HandlerFunction, std::unordered_map<std::string, std::string>> find_handler(
                const std::string& method,
                const std::string& path
            );

            network::Socket _socket;
    };
}