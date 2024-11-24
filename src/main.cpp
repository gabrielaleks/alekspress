#include <iostream>
#include <http_server/alekspress.hpp>

int main() {
    server::Alekspress app(8080);

    /** Example usage of Alekspress
     * 
     * app.get("/hello", [](const server::Request& req) -> server::Response {
     *   return server::Response::ok("Hello, World!");
     * });
     * 
     * app.post("/user", [](const server::Request& req) -> server::Response {
     *   ...
     *   server::Response response;
     *   response.set_body("created user!");
     *   response.set_header("my-header", "was-added");
     *   response.set_status_code(200);
     *   return response;
     * })
     */

    app.run();
}
