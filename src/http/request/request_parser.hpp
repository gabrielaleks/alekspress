#pragma once

#include <string>

namespace internal {
    namespace request {
        class RequestParser {
            public:
                RequestParser() = default;

                void append_to_request(const char* buffer, ssize_t bytes_read);

                bool is_request_complete();
                
                const std::string complete_request() { return _complete_request; }

                const static size_t READ_BUFFER_SIZE = 1024;
            private:
                const size_t MAX_REQUEST_SIZE = 1 * 1024 * 1024;
            
                std::string _complete_request;
                std::string _method;
                bool _is_request_complete = false;
                bool _is_headers_complete = false;
                ssize_t _body_bytes_received = 0;
                ssize_t _expected_content_length = -1;

                int parse_content_length(const std::string& headers_lowercased);
        };
    }
}
