// Public request interface
#pragma once

#include "http/request/request.hpp"
#include <string>
#include <unordered_map>

namespace alekspress {
    class Request {
        public:
            Request() = default;

            static Request from_raw_request(
                internal::request::Request internal_request,
                std::unordered_map<std::string, std::string> params
            );

            std::string method() const { return _method; }
            std::string path() const { return _path; }
            std::string http_version() const { return _http_version; }
            std::unordered_map<std::string, std::string> headers() const { return _headers; }
            std::string body() const { return _body; }
            std::string param(const std::string& name) const;
        private:
            std::string _method;
            std::string _path;
            std::string _http_version;
            std::unordered_map<std::string, std::string> _headers;
            std::string _body;
            std::unordered_map<std::string, std::string> _params;
    };
}