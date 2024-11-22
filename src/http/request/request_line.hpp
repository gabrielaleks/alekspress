#pragma once

#include <string>
#include <string_view>
#include <unordered_set>
#include <algorithm>

namespace http {
    namespace request {
        class RequestLine {
        public:
            RequestLine() = default;

            RequestLine(
                std::string method,
                std::string path,
                std::string version
            );

            static RequestLine from_string(const std::string_view& http_request_line_string);

            std::string_view method() const { return _method; }
            std::string_view path() const { return _path; }
            std::string_view http_version() const { return _http_version; }

            std::string to_string() const;

        private:
            std::string _method;
            std::string _path;
            std::string _http_version;

            static const std::unordered_set<std::string> validMethods;
            static const std::unordered_set<std::string> validHttpVersions;

            void validate() const;
            static bool is_valid_method(const std::string_view& method);
            static bool is_valid_http_version(const std::string_view& http_version);
        };
    }  // namespace request
}  // namespace http
