#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <string_view>
#include "request_line.hpp"
#include "headers.hpp"
#include "body.hpp"

namespace http {
    namespace request {
        class HttpRequest {
        public:
            HttpRequest() = default;

            HttpRequest(
                RequestLine request_line,
                Headers headers,
                Body body
            );

            static HttpRequest from_char_buffer(const char* http_request_char_buffer);

            RequestLine request_line() const { return _request_line; }
            Headers headers() const { return _headers; }
            Body body() const { return _body; }

            std::string to_string() const;

        private:
            RequestLine _request_line;
            Headers _headers;
            Body _body;
        };
    }  // namespace request
}  // namespace http

#endif