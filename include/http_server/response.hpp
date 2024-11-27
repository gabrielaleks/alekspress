// Public response interface
#pragma once

#include <string>
#include <unordered_map>
#include <http_server/status_code.hpp>

namespace internal {
    namespace response {
        class Response;
    }
}

namespace alekspress {
    class Response {
        public:
            Response() = default;

            Response(int status_code, std::string body);

            void set_status_code(int status_code);
            void set_header(std::string key, std::string value);
            void set_body(std::string body);

            // Standard responses
            static Response ok(std::string body);
        private:
            std::string _http_version = "HTTP/1.1";
            int _status_code = StatusCode::OK;
            std::unordered_map<std::string, std::string> _headers;
            std::string _body;

            friend class internal::response::Response;
    };
}