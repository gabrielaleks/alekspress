#include "http_request.hpp"
#include <vector>

namespace http {
    namespace request {
        HttpRequest::HttpRequest(
            RequestLine request_line,
            Headers headers,
            Body body
        ) : _request_line(std::move(request_line)), _headers(std::move(headers)), _body(std::move(body)) {
        }

        HttpRequest HttpRequest::from_string(const std::string http_request_string) {
            std::vector<std::string> header_lines;

            // Extract body index and body content
            size_t body_separator = http_request_string.find("\r\n\r\n", 0);
            size_t body_start = body_separator + 4;
            std::string body_string = http_request_string.substr(body_start);

            // Extract lines http header lines
            size_t start = 0, end = 0;
            while ((end = http_request_string.find("\r\n", start)) != std::string::npos && start + 2 < body_start) {
                header_lines.push_back(http_request_string.substr(start, end - start));
                start = end + 2;
            }

            RequestLine request_line = RequestLine::from_string(header_lines[0]);

            Headers headers = Headers::from_vector({header_lines.begin() + 1, header_lines.end()});

            Body body = Body::from_string(body_string);

            HttpRequest http_request = HttpRequest(
                request_line,
                headers,
                body
            );

            return http_request;
        }

        std::string HttpRequest::to_string() const {
            return _request_line.to_string();
        }
    };  // namespace request
}  // namespace http