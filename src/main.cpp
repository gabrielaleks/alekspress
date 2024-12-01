#include <iostream>
#include <http_server/alekspress.hpp>

int main() {
    alekspress::Alekspress app(8080);

    app.get("/hello", [](const alekspress::Request& req) -> alekspress::Response {
        return alekspress::Response::ok("Hello user: " + req.param("id"));
    });

    app.get("/hello/:id", [](const alekspress::Request& req) -> alekspress::Response {
        return alekspress::Response::ok("Hello user: " + req.param("id"));
    });

    app.post("/hello/:id", [](const alekspress::Request& req) -> alekspress::Response {
        return alekspress::Response::ok("Hello user: " + req.param("id"));
    });

    /** How to implement this?
     * app.post("/example",  [](const alekspress::Request& req) -> alekspress::Response {
     *     auto json_response = Response::Builder()
     *         .status(StatusCode::OK)
     *         .json({"message": "success"})
     *         .build();
     *     return json_response;
     * });
    */

    app.run();
}
