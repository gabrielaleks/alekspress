#pragma once

#include "status_line.hpp"
#include "headers.hpp"
#include "body.hpp"
#include <http_server/response.hpp>

namespace internal {
    namespace response {
        class Response {
            public:
                Response() = default;

                Response(
                    StatusLine status_line,
                    Headers headers,
                    Body body
                );

                static Response from_public_response(const alekspress::Response& public_response);
                
                std::string serialize();
            private:
                StatusLine _status_line;
                Headers _headers;
                Body _body;
        };
    }
}