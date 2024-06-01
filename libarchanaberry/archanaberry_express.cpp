#include "archanaberry_express.hpp"
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

namespace archanaberry {
namespace express {

AppWeb::AppWeb() {}

void AppWeb::get(const std::string& path, RouteHandler handler) {
    std::lock_guard<std::mutex> lock(mutex_);
    routes_[path] = handler;
}

void AppWeb::listen(int port) {
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::acceptor acceptor(io_service,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        boost::asio::ip::tcp::socket socket(io_service);
        acceptor.accept(socket);

        std::thread(&AppWeb::handleRequest, this, std::move(socket)).detach();
    }
}

void AppWeb::handleRequest(boost::asio::ip::tcp::socket socket) {
    boost::asio::ip::tcp::iostream stream(std::move(socket));

    std::string request;
    std::getline(stream, request);

    std::string method, path;
    std::istringstream request_stream(request);
    request_stream >> method >> path;

    // Consume the remaining headers
    std::string header;
    while (std::getline(stream, header) && header != "\r") {
        // Optional: Process headers if needed
    }

    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto route = routes_.find(path);
        if (route != routes_.end()) {
            route->second(stream);
        } else {
            stream << "HTTP/1.1 404 Not Found\r\n";
            stream << "Content-Type: text/plain\r\n";
            stream << "Connection: close\r\n\r\n";
            stream << "404 Not Found";
        }
    }
    stream.flush();
}

} // namespace express
} // namespace archanaberry
