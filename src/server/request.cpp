#include <http_server/request.hpp>

namespace alekspress {
    Request Request::from_internal_request(internal::request::Request internal_request) {
        Request request;

        request._method = internal_request.request_line().method();
        request._path = internal_request.request_line().path();
        request._http_version = internal_request.request_line().http_version();
        request._headers = internal_request.headers().all();
        request._body = internal_request.body().to_string();

        return request;
    }
}