#include "body.hpp"

namespace http {
    namespace request {
        Body::Body(std::string body): _body(std::move(body)) {
        }

        Body Body::from_string(std::string body_string) {
            return Body(body_string);
        }
    }
}