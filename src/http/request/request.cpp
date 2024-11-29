#include "request.hpp"
#include <vector>
#include <iostream>

namespace internal {
    namespace request {
        Request::Request(
            RequestLine request_line,
            Headers headers,
            Body body
        ) : _request_line(std::move(request_line)), _headers(std::move(headers)), _body(std::move(body)) {
            validate();

            // Debugging
            std::cout << "< HTTP Request Line" << std::endl;
            std::cout << _request_line.method() << std::endl;
            std::cout << _request_line.path() << std::endl;
            std::cout << _request_line.http_version() << std::endl;
            std::cout << "< HTTP Request Headers" << std::endl;
            _headers.print_all();
            std::cout << "< HTTP Request Body" << std::endl;
            std::cout << _body.to_string() << std::endl;
            std::cout << "\n-----\n" << std::endl;
            // ---
        }

        void Request::validate() const {
            bool is_content_length_zeroed_or_undefined = _headers.content_length() == "0" || _headers.content_length() == "";

            if (
                is_content_length_zeroed_or_undefined &&
                _body.to_string().length() != 0
            ) {
                throw std::invalid_argument("[411] Missing Content-Length");
            }
            
            if (
                !is_content_length_zeroed_or_undefined &&
                _body.to_string().length() == 0
            ) {
                throw std::invalid_argument("[400] Content-Length is not zero but body is empty");
            }

            if (
                !is_content_length_zeroed_or_undefined &&
                (size_t)stoi(_headers.content_length()) != _body.to_string().length()
            ) {
                throw std::invalid_argument("[400] Content-Length does not match body");
            }

            // Ensure methods without body do not contain a body
            bool is_method_without_body = METHODS_WITHOUT_BODY.find(_request_line.method()) != METHODS_WITHOUT_BODY.end();
            if (is_method_without_body && !is_content_length_zeroed_or_undefined) {
                throw std::invalid_argument("[400] Request method does not support a body");
            }

            // Ensure the body mathces the format specified by the Content-Type (JSON, XML etc)
        }

        const std::unordered_set<std::string> Request::METHODS_WITHOUT_BODY {
            "GET",
            "HEAD",
            "DELETE",
            "OPTIONS"
        };

        Request Request::from_string(const std::string http_request_string) {
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

            Request http_request = Request(
                request_line,
                headers,
                body
            );

            return http_request;
        }

        std::string Request::to_string() const {
            return _request_line.to_string();
        }
    };  // namespace request
}  // namespace internal