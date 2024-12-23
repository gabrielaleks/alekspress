// Public response interface
#pragma once

#include <string>
#include <unordered_map>
#include <alekspress/status_code.hpp>

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
            int _status_code = StatusCode::OK;
            std::unordered_map<std::string, std::string> _headers;
            std::string _body;

            friend class internal::response::Response;
    };
}