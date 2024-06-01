#include "archanaberry.hpp"

using namespace archanaberry::express;

AppWeb::AppWeb(const std::string& address, unsigned short port)
    : acceptor_(ioc_, tcp::endpoint(ip::make_address(address), port)) {}

void AppWeb::route(const std::string& path, request_handler_t handler) {
    routes_[path] = handler;
}

void AppWeb::run() {
    do_accept();
    for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads_.emplace_back([this] {
            this->worker_thread();
        });
    }
    for (auto& t : threads_) {
        t.join();
    }
}

void AppWeb::do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket), routes_)->start();
        }
        do_accept();
    });
}

void AppWeb::worker_thread() {
    ioc_.run();
}

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, std::unordered_map<std::string, request_handler_t>& routes)
        : socket_(std::move(socket)), routes_(routes) {}

    void start() {
        do_read();
    }

private:
    void do_read() {
        auto self(shared_from_this());
        http::async_read(socket_, buffer_, request_,
                         [this, self](boost::system::error_code ec, std::size_t) {
                             if (!ec) {
                                 handle_request();
                             }
                         });
    }

    void handle_request() {
        auto self(shared_from_this());
        http::response<http::string_body> res{http::status::ok, request_.version()};
        res.set(http::field::server, "ArchanaBerry Express");
        res.set(http::field::content_type, "text/html");

        auto path = request_.target().to_string();
        if (routes_.find(path) != routes_.end()) {
            routes_[path](request_, res);
        } else {
            res.result(http::status::not_found);
            res.body() = "The resource '" + path + "' was not found.";
        }
        res.prepare_payload();

        http::async_write(socket_, res, [this, self](boost::system::error_code ec, std::size_t) {
            socket_.shutdown(tcp::socket::shutdown_send, ec);
        });
    }

    tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    http::request<http::string_body> request_;
    std::unordered_map<std::string, request_handler_t>& routes_;
};
