#include "../libarchanaberry/archanaberry_express.hpp"
#include <string>

int main() {
    archanaberry::express::AppWeb app;                                                             
    app.get("/", [](boost::asio::ip::tcp::iostream& stream) {
        stream << "HTTP/1.1 200 OK\r\n";                                                                   stream << "Content-Type: text/html\r\n";
        stream << "Connection: close\r\n\r\n";
        stream << R"(                                                                                          <!DOCTYPE html>                                                                                    <html>
            <head>                                                                                                 <title>Hello, I'am Archana Berry UwU</title>                                                       <style>                                                                                                body { font-family: Arial, sans-serif; }                                                           .archanaberrydev {                                                                                     position: absolute;                                                                                top: 30%;                                                                                          zoom: 2;                                                                                           left: -4%;                                                                                         transform: rotate(45deg);                                                                      }                                                                                              </style>                                                                                       </head>                                                                                            <body>                                                                                                 <h1>Hello, I'am Archana Berry UwU</h1>                                                             <img class="archanaberrydev" src="berry.png" alt="Archana Berry">
                <script>
                    console.log('Hello from JavaScript');
                </script>
            </body>                                                                                            </html>
        )";
        stream.flush();
    });

    app.listen(8080);

    return 0;
}
