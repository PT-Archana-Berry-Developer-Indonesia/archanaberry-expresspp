#ifndef ARCHANABERRY_HPP
#define ARCHANABERRY_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/thread.hpp>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <unordered_map>

namespace archanaberry {
    namespace express {
        using namespace boost::asio;
        using tcp = ip::tcp;
        namespace http = boost::beast::http;
        using request_handler_t = std::function<void(http::request<http::string_body>&, http::response<http::string_body>&)>;

        class AppWeb {
        public:
            AppWeb(const std::string& address, unsigned short port);
            void route(const std::string& path, request_handler_t handler);
            void run();

        private:
            void do_accept();
            void worker_thread();

            io_context ioc_;
            tcp::acceptor acceptor_;
            std::vector<std::thread> threads_;
            std::unordered_map<std::string, request_handler_t> routes_;
        };
    }
}

#endif // ARCHANABERRY_HPP
