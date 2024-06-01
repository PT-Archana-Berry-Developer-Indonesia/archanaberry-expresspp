#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

namespace archanaberry {
namespace express {

class Session : public std::enable_shared_from_this<Session> {
public:
    using RequestHandler = std::function<void(boost::beast::http::request<boost::beast::http::string_body>&, boost::beast::http::response<boost::beast::http::string_body>&)>;

    Session(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, RequestHandler>& routes);

    void start();

private:
    void do_read();
    void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
    void do_write(boost::system::error_code ec, std::size_t bytes_transferred);

    boost::asio::ip::tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    boost::beast::http::request<boost::beast::http::string_body> req_;
    boost::beast::http::response<boost::beast::http::string_body> res_;
    std::unordered_map<std::string, RequestHandler>& routes_;
};

} // namespace express
} // namespace archanaberry

#endif // SESSION_HPP
