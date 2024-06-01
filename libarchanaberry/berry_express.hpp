#ifndef BERRY_EXPRESS_HPP
#define BERRY_EXPRESS_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace archanaberry {
namespace express {

using RequestHandler = std::function<void(boost::beast::http::request<boost::beast::http::string_body>&, boost::beast::http::response<boost::beast::http::string_body>&)>;

class Session; // Forward declaration

class AppWeb {
public:
    AppWeb(const std::string& address, unsigned short port);
    void route(const std::string& path, RequestHandler handler);
    void run();

private:
    void do_accept();
    void worker_thread();

    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<std::string, RequestHandler> routes_;
    std::vector<std::thread> threads_;
};

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, RequestHandler>& routes);
    void start();

private:
    void do_read();
    void handle_request();
    void do_write();

    boost::asio::ip::tcp::socket socket_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::beast::flat_buffer buffer_;
    boost::beast::http::request<boost::beast::http::string_body> req_;
    boost::beast::http::response<boost::beast::http::string_body> res_;
    std::unordered_map<std::string, RequestHandler>& routes_;
};

} // namespace express
} // namespace archanaberry

#endif // BERRY_EXPRESS_HPP
