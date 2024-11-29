#pragma once

#include <string>
#include <string_view>
#include <unordered_set>
#include <algorithm>

namespace internal {
    namespace request {
        class RequestLine {
        public:
            RequestLine() = default;

            RequestLine(
                std::string method,
                std::string path,
                std::string version
            );

            static RequestLine from_string(const std::string& http_request_line_string);

            std::string method() const { return _method; }
            std::string path() const { return _path; }
            std::string http_version() const { return _http_version; }

            std::string to_string() const;

        private:
            std::string _method;
            std::string _path;
            std::string _http_version;

            static const std::unordered_set<std::string> SUPPORTED_METHODS;
            static const std::unordered_set<std::string> SUPPORTED_HTTP_VERSIONS;

            void validate() const;
            static bool is_supported_method(const std::string_view& method);
            static bool is_supported_http_version(const std::string_view& http_version);
        };
    }  // namespace request
}  // namespace internal
