#pragma once

#include "status_line.hpp"
#include "headers.hpp"
#include "body.hpp"
#include <alekspress/response.hpp>
#include <exceptions/http_exceptions.hpp>

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

                static Response from_user_response(const alekspress::Response& public_response);
                static Response from_exception(const exceptions::HttpException& exception);
                
                std::string serialize();
            private:
                StatusLine _status_line;
                Headers _headers;
                Body _body;
        };
    }
}