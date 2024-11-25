#include "body.hpp"

namespace internal {
    namespace request {
        Body::Body(std::string body): _body(std::move(body)) {
        }

        Body Body::from_string(const std::string& body_string) {
            return Body(body_string);
        }
    }
}