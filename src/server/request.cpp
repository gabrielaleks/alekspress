#include <alekspress/request.hpp>

namespace alekspress {
    Request Request::from_raw_request(
        internal::request::Request raw_request,
        std::unordered_map<std::string, std::string> params
    ) {
        Request request;

        request._method = raw_request.request_line().method();
        request._path = raw_request.request_line().path();
        request._http_version = raw_request.request_line().http_version();
        request._headers = raw_request.headers().all();
        request._body = raw_request.body().to_string();
        request._params = params;

        return request;
    }

    std::string Request::param(const std::string& name) const {
        auto it = _params.find(name);
        return it != _params.end() ? it->second : "";
    }
}