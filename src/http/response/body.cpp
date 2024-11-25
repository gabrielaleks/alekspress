#include "body.hpp"

namespace internal {
    namespace response {
        Body::Body(std::string body): _body(std::move(body)) {
        }
    }
}