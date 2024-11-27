#include <http_server/request.hpp>

namespace alekspress {
    Request Request::from_raw_request(internal::request::Request raw_request) {
        Request request;

        request._method = raw_request.request_line().method();
        request._path = raw_request.request_line().path();
        request._http_version = raw_request.request_line().http_version();
        request._headers = raw_request.headers().all();
        request._body = raw_request.body().to_string();

        return request;
    }
}