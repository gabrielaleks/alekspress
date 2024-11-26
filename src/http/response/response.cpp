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

        Response Response::from_public_response(const alekspress::Response& public_response) {
            StatusLine status_line(public_response._http_version, public_response._status_code);

            Body body(public_response._body);

            Headers headers;
            headers.add_default_headers(public_response._body.length());
            for (auto const& [key, value] : public_response._headers) {
                headers.add(key, value);
            }

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