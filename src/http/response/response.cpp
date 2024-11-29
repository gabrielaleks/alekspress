#include "response.hpp"
#include <iostream>

namespace internal {
    namespace response {
        Response::Response (
            StatusLine status_line,
            Headers headers,
            Body body
        ) : _status_line(std::move(status_line)), _headers(std::move(headers)), _body(std::move(body))  {
        }

        Response Response::from_user_response(const alekspress::Response& user_response) {
            StatusLine status_line(StatusLine::DEFAULT_HTTP_VERSION, user_response._status_code);

            Body body(user_response._body);

            Headers headers;
            headers.add_default_headers(user_response._body.length());
            for (auto const& [key, value] : user_response._headers) {
                headers.add(key, value);
            }

            return Response(status_line, headers, body);
        }

        Response Response::from_exception(const exceptions::HttpException& exception) {
            StatusLine status_line(StatusLine::DEFAULT_HTTP_VERSION, exception.status_code());

            Body body(exception.message());

            Headers headers;
            headers.add_default_headers(exception.message().length());

            return Response(status_line, headers, body);
        }

        std::string Response::serialize() {
            // Debugging
            std::cout << "> HTTP Response Status Line" << std::endl;
            std::cout << _status_line.serialize() << std::endl;
            std::cout << "> HTTP Response Headers" << std::endl;
            std::cout << _headers.serialize() << std::endl;
            std::cout << "> HTTP Response Body" << std::endl;
            std::cout << _body.serialize() << std::endl;
            std::cout << "\n-----\n" << std::endl;
            return _status_line.serialize() + _headers.serialize() + "\r\n" +  _body.serialize();
        }
    }
}