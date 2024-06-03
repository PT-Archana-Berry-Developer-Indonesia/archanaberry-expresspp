#ifndef ARCHANABERRY_EXPRESS_HPP
#define ARCHANABERRY_EXPRESS_HPP

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <boost/asio.hpp>
#include "archanaberry_mimetypes.hpp" // Tambahkan include

namespace archanaberry {
    namespace express {

        class AppWeb {
        public:
            using Handler = std::function<void(std::ostream&)>;

            AppWeb() {}

            void get(const std::string& path, Handler handler);
            void serveStatic(const std::string& directory);

            void listen(int port);

        private:
            void handle_request(const std::string& request, std::ostream& response_stream);
            void serve_file(const std::string& path, std::ostream& response_stream);

            std::unordered_map<std::string, Handler> routes_;
            std::string static_directory_;
        };

        extern AppWeb appweb;

    } // namespace express
} // namespace archanaberry

#endif // ARCHANABERRY_EXPRESS_HPP
