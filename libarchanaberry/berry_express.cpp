#include "berry_express.hpp"
#include <boost/beast.hpp>

namespace archanaberry {
namespace express {

AppWeb::AppWeb(const std::string& address, unsigned short port)
    : acceptor_(ioc_, {boost::asio::ip::make_address(address), port}) {
}

void AppWeb::route(const std::string& path, RequestHandler handler) {
    routes_[path] = handler;
}

void AppWeb::run() {
    for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads_.emplace_back([this] {
            worker_thread();
        });
    }

    do_accept();
    ioc_.run();

    for (auto& t : threads_) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void AppWeb::do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
        if (!ec) {
            auto session = std::make_shared<Session>(std::move(socket), routes_);
            session->start();
        }
        do_accept();
    });
}

void AppWeb::worker_thread() {
    ioc_.run();
}

Session::Session(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, RequestHandler>& routes)
    : socket_(std::move(socket)), strand_(socket_.get_executor().context()), routes_(routes) {}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self = shared_from_this();
    boost::beast::http::async_read(socket_, buffer_, req_, boost::asio::bind_executor(strand_, [self](boost::system::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (!ec) {
            self->handle_request();
        }
    }));
}

void Session::handle_request() {
    auto self = shared_from_this();
    auto path = req_.target().to_string();
    auto it = routes_.find(path);
    if (it != routes_.end()) {
        res_.version(req_.version());
        res_.set(boost::beast::http::field::server, "Boost.Beast");
        res_.keep_alive(req_.keep_alive());

        it->second(req_, res_);
    } else {
        res_.result(boost::beast::http::status::not_found);
        res_.version(req_.version());
        res_.set(boost::beast::http::field::server, "Boost.Beast");
        res_.keep_alive(req_.keep_alive());
        res_.body() = "Not Found";
        res_.prepare_payload();
    }

    do_write();
}

void Session::do_write() {
    auto self = shared_from_this();
    boost::beast::http::async_write(socket_, res_, boost::asio::bind_executor(strand_, [self](boost::system::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (!ec) {
            if (self->res_.need_eof()) {
                boost::system::error_code ec;
                self->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
            }
        }
    }));
}

} // namespace express
} // namespace archanaberry
