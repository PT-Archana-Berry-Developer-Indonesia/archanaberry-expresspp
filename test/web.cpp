#include "../libarchanaberry/archanaberry_express.hpp"
#include <string>

int main() {
    archanaberry::express::AppWeb app;

    app.get("/", [](boost::asio::ip::tcp::iostream& stream) {
        stream << "HTTP/1.1 200 OK\r\n";
        stream << "Content-Type: text/html\r\n";
        stream << "Connection: close\r\n\r\n";
        stream << R"(
            <!DOCTYPE html>
            <html>
            <head>
                <title>Hello, World!</title>
                <style>
                    body { font-family: Arial, sans-serif; }
                </style>
            </head>
            <body>
                <h1>Hello, World!</h1>
                <script>
                    console.log('Hello from JavaScript');
                </script>
            </body>
            </html>
        )";
        stream.flush();
    });

    app.listen(8080);

    return 0;
}