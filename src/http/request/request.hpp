#pragma once

#include <string>
#include <string_view>
#include "request_line.hpp"
#include "headers.hpp"
#include "body.hpp"

namespace internal {
    namespace request {
        class Request {
        public:
            Request() = default;

            Request(
                RequestLine request_line,
                Headers headers,
                Body body
            );

            static Request from_string(const std::string http_request_char_buffer);

            RequestLine request_line() const { return _request_line; }
            Headers headers() const { return _headers; }
            Body body() const { return _body; }

            std::string to_string() const;

        private:
            RequestLine _request_line;
            Headers _headers;
            Body _body;

            static const std::unordered_set<std::string> METHODS_WITHOUT_BODY;

            void validate() const;
        };
    }  // namespace request
}  // namespace internal
