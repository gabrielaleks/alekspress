#include <http_server/response.hpp>

namespace alekspress {
    Response::Response(
        int status_code,
        std::string body
    ) : _status_code(status_code), _body(body) {
    }
    
    void Response::set_status_code(int status_code) {
        _status_code = status_code;
    }

    void Response::set_header(std::string key, std::string value) {
        _headers[key] = value;
    }

    void Response::set_body(std::string body) {
        _body = body;
    }

    Response Response::ok(std::string body) {
        return Response(200, body);
    }
}