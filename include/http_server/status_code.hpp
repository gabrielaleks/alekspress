#pragma once

namespace alekspress {
    class StatusCode {
        public:
            // Information responses
            static constexpr int CONTINUE = 100;
            static constexpr int SWITCHING_PROTOCOLS = 101;
            static constexpr int PROCESSING = 102;
            static constexpr int EARLY_HINTS = 103;
        
            // Successful responses
            static constexpr int OK = 200;
            static constexpr int CREATED = 201;
            static constexpr int ACCEPTED = 202;
            static constexpr int NON_AUTHORITATIVE_INFORMATION = 203;
            static constexpr int NO_CONTENT = 204;
            static constexpr int RESET_CONTENT = 205;
            static constexpr int PARTIAL_CONTENT = 206;
            static constexpr int MULTI_STATUS = 207;
            static constexpr int ALREADY_REPORTED = 208;
            static constexpr int IM_USED = 226;

            // Redirection messages
            static constexpr int MULTIPLE_CHOICES = 300;
            static constexpr int MOVED_PERMANENTLY = 301;
            static constexpr int FOUND = 302;
            static constexpr int SEE_OTHER = 303;
            static constexpr int NOT_MODIFIED = 304;
            static constexpr int USE_PROXY = 305;
            static constexpr int TEMPORARY_REDIRECT = 307;
            static constexpr int PERMANENT_REDIRECT = 308;

            // Client error responses
            static constexpr int BAD_REQUEST = 400;
            static constexpr int UNAUTHORIZED = 401;
            static constexpr int PAYMENT_REQUIRED = 402;
            static constexpr int FORBIDDEN = 403;
            static constexpr int NOT_FOUND = 404;
            static constexpr int METHOD_NOT_ALLOWED = 405;
            static constexpr int NOT_ACCEPTABLE = 406;
            static constexpr int PROXY_AUTHENTICATION_REQUIRED = 407;
            static constexpr int REQUEST_TIMEOUT = 408;
            static constexpr int CONFLICT = 409;
            static constexpr int GONE = 410;
            static constexpr int LENGTH_REQUIRED = 411;
            static constexpr int PRECONDITION_FAILED = 412;
            static constexpr int CONTENT_TOO_LARGE = 413;
            static constexpr int URI_TOO_LONG = 414;
            static constexpr int UNSUPPORTED_MEDIA_TYPE = 415;
            static constexpr int RANGE_NOT_SATISFIABLE = 416;
            static constexpr int EXPECTATION_FAILED = 417;
            static constexpr int IM_A_TEA_POT = 418;
            static constexpr int MISDIRECTED_REQUEST = 421;
            static constexpr int UNPROCESSABLE_CONTENT = 422;
            static constexpr int LOCKED = 423;
            static constexpr int FAILED_DEPENDENCY = 424;
            static constexpr int TOO_EARLY = 425;
            static constexpr int UPGRADE_REQUIRED = 426;
            static constexpr int PRECONDITION_REQUIRED = 428;
            static constexpr int TOO_MANY_REQUESTS = 429;
            static constexpr int REQUEST_HEADER_FIELDS_TOO_LARGE = 431;
            static constexpr int UNAVAILABLE_FOR_LEGAL_REASONS = 451;

            // Server error responses
            static constexpr int INTERNAL_SERVER_ERROR = 500;
            static constexpr int NOT_IMPLEMENTED = 501;
            static constexpr int BAD_GATEWAY = 502;
            static constexpr int SERVICE_UNAVAILABLE = 503;
            static constexpr int GATEWAY_TIMEOUT = 504;
            static constexpr int HTTP_VERSION_NOT_SUPPORTED = 505;
            static constexpr int VARIANT_ALSO_NEGOTIATES = 506;
            static constexpr int INSUFFICIENT_STORAGE = 507;
            static constexpr int LOOP_DETECTED = 508;
            static constexpr int NOT_EXTENDED = 510;
            static constexpr int NETWORK_AUTHENTICATION_REQUIRED = 511;
    };
}