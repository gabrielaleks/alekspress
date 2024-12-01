#include "status_line.hpp"
#include <iostream>
#include <alekspress/status_code.hpp>

namespace internal {
    namespace response {
        StatusLine::StatusLine(
            std::string http_version,
            int status_code
        ) : 
            _http_version(std::move(http_version)),
            _status_code(std::move(status_code)) {
        }

        void StatusLine::set_http_version(std::string http_version) {
            _http_version = http_version;
        }

        void StatusLine::set_status_code(int status_code) {
            _status_code = status_code;
        }

        std::string StatusLine::serialize() {
            return _http_version
                + " "
                + std::to_string(_status_code)
                + " "
                + get_status_text_from_status_code(_status_code)
                + "\r\n";
        }

        const std::string& StatusLine::get_status_text_from_status_code(int code) {
            auto it = STATUS_TEXTS.find(code);
            if (it != STATUS_TEXTS.end()) {
                return it->second;
            }
            static const std::string UNKNOWN = "Unknown";
            return UNKNOWN;
        }

        const std::unordered_map<int, std::string> StatusLine::STATUS_TEXTS = {
            // Information responses
            {alekspress::StatusCode::CONTINUE, "Continue"},
            {alekspress::StatusCode::SWITCHING_PROTOCOLS, "Switching Protocols"},
            {alekspress::StatusCode::PROCESSING, "Processing"},
            {alekspress::StatusCode::EARLY_HINTS, "Early Hints"},

            // Successful responses
            {alekspress::StatusCode::OK, "Ok"},
            {alekspress::StatusCode::CREATED, "Created"},
            {alekspress::StatusCode::ACCEPTED, "Accepted"},
            {alekspress::StatusCode::NON_AUTHORITATIVE_INFORMATION, "Non-Authoritative Information"},
            {alekspress::StatusCode::NO_CONTENT, "No Content"},
            {alekspress::StatusCode::RESET_CONTENT, "Reset Content"},
            {alekspress::StatusCode::PARTIAL_CONTENT, "Partial Content"},
            {alekspress::StatusCode::MULTI_STATUS, "Multi-Status"},
            {alekspress::StatusCode::ALREADY_REPORTED, "Already Reported"},
            {alekspress::StatusCode::IM_USED, "IM Used"},

            // Redirection messages
            {alekspress::StatusCode::MULTIPLE_CHOICES, "Multiple Choices"},
            {alekspress::StatusCode::MOVED_PERMANENTLY, "Moved Permanently"},
            {alekspress::StatusCode::FOUND, "Found"},
            {alekspress::StatusCode::SEE_OTHER, "See Other"},
            {alekspress::StatusCode::NOT_MODIFIED, "Not Modified"},
            {alekspress::StatusCode::USE_PROXY, "Use Proxy"},
            {alekspress::StatusCode::TEMPORARY_REDIRECT, "Temporary Redirect"},
            {alekspress::StatusCode::PERMANENT_REDIRECT, "Permanent Redirect"},

            // Client error responses
            {alekspress::StatusCode::BAD_REQUEST, "Bad Request"},
            {alekspress::StatusCode::UNAUTHORIZED, "Unauthorized"},
            {alekspress::StatusCode::PAYMENT_REQUIRED, "Payment Required"},
            {alekspress::StatusCode::FORBIDDEN, "Forbidden"},
            {alekspress::StatusCode::NOT_FOUND, "Not Found"},
            {alekspress::StatusCode::METHOD_NOT_ALLOWED, "Method Not Allowed"},
            {alekspress::StatusCode::NOT_ACCEPTABLE, "Not Acceptable"},
            {alekspress::StatusCode::PROXY_AUTHENTICATION_REQUIRED, "Proxy Authentication Required"},
            {alekspress::StatusCode::REQUEST_TIMEOUT, "Request Timeout"},
            {alekspress::StatusCode::CONFLICT, "Conflict"},
            {alekspress::StatusCode::GONE, "Gone"},
            {alekspress::StatusCode::LENGTH_REQUIRED, "Length Required"},
            {alekspress::StatusCode::PRECONDITION_FAILED, "Precondition Failed"},
            {alekspress::StatusCode::CONTENT_TOO_LARGE, "Content Too Large"},
            {alekspress::StatusCode::URI_TOO_LONG, "URI Too Long"},
            {alekspress::StatusCode::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"},
            {alekspress::StatusCode::RANGE_NOT_SATISFIABLE, "Range Not Satisfiable"},
            {alekspress::StatusCode::EXPECTATION_FAILED, "Expectation Failed"},
            {alekspress::StatusCode::IM_A_TEA_POT, "I'm a teapot"},
            {alekspress::StatusCode::MISDIRECTED_REQUEST, "Misdirected Request"},
            {alekspress::StatusCode::UNPROCESSABLE_CONTENT, "Unprocessable Content"},
            {alekspress::StatusCode::LOCKED, "Locked"},
            {alekspress::StatusCode::FAILED_DEPENDENCY, "Faile dDependency"},
            {alekspress::StatusCode::TOO_EARLY, "Too Early"},
            {alekspress::StatusCode::UPGRADE_REQUIRED, "Upgrade Required"},
            {alekspress::StatusCode::PRECONDITION_REQUIRED, "Precondition Required"},
            {alekspress::StatusCode::TOO_MANY_REQUESTS, "Too Many Requests"},
            {alekspress::StatusCode::REQUEST_HEADER_FIELDS_TOO_LARGE, "Request Header Fields Too Large"},
            {alekspress::StatusCode::UNAVAILABLE_FOR_LEGAL_REASONS, "Unavailable For Legal Reasons"},

            // Server error responses
            {alekspress::StatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error"},
            {alekspress::StatusCode::NOT_IMPLEMENTED, "Not Implemented"},
            {alekspress::StatusCode::BAD_GATEWAY, "Bad Gateway"},
            {alekspress::StatusCode::SERVICE_UNAVAILABLE, "Service Unavailable"},
            {alekspress::StatusCode::GATEWAY_TIMEOUT, "Gateway Timeout"},
            {alekspress::StatusCode::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"},
            {alekspress::StatusCode::VARIANT_ALSO_NEGOTIATES, "Variant Also Negotiates"},
            {alekspress::StatusCode::INSUFFICIENT_STORAGE, "Insufficient Storage"},
            {alekspress::StatusCode::LOOP_DETECTED, "Loop Detected"},
            {alekspress::StatusCode::NOT_EXTENDED, "Not Extended"},
            {alekspress::StatusCode::NETWORK_AUTHENTICATION_REQUIRED, "Network Authentication Required"}
        };
    }
}