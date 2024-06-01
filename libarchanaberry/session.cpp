#include "session.hpp"

namespace archanaberry {
namespace express {

Session::Session(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, RequestHandler>& routes)
    : socket_(std::move(socket)), routes_(routes) {
}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    boost::beast::http::async_read(socket_, buffer_, req_,
        [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
            on_read(ec, bytes_transferred);
        });
}

void Session::on_read(boost::system::error_code ec, std::size_t bytes_transferred) {
    if (!ec) {
        auto it = routes_.find(req_.target().to_string());
        if (it != routes_.end()) {
            it->second(req_, res_);
        } else {
            res_.result(boost::beast::http::status::not_found);
            res_.body() = "The resource was not found.";
        }
        res_.prepare_payload();

        auto self(shared_from_this());
        boost::beast::http::async_write(socket_, res_,
            [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                do_write(ec, bytes_transferred);
            });
    }
}

void Session::do_write(boost::system::error_code ec, std::size_t bytes_transferred) {
    if (!ec) {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
    }
}

} // namespace express
} // namespace archanaberry
