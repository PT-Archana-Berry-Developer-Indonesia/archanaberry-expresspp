#ifndef ARCHANABERRY_EXPRESS_HPP
#define ARCHANABERRY_EXPRESS_HPP

#include <string>
#include <functional>
#include <unordered_map>
#include <thread>
#include <vector>
#include <mutex>
#include <boost/asio.hpp>

namespace archanaberry {
namespace express {

class AppWeb {
public:
    using RouteHandler = std::function<void(boost::asio::ip::tcp::iostream&)>;

    AppWeb();

    void get(const std::string& path, RouteHandler handler);

    void listen(int port);

private:
    void handleRequest(boost::asio::ip::tcp::socket socket);

    std::unordered_map<std::string, RouteHandler> routes_;
    std::vector<std::thread> thread_pool_;
    std::mutex mutex_;
};

} // namespace express
} // namespace archanaberry

#endif // ARCHANABERRY_EXPRESS_HPP
