#include "../libarchanaberry/archanaberry_express.hpp"
#include <string>

const std::string html = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>SVG Gallery</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    padding: 20px;
                    margin: 0;
                }
                .header {
                    display: flex;
                    justify-content: space-between;
                    align-items: center;
                    padding: 10px 0;
                }
                .header input[type="text"] {
                    padding: 5px;
                    font-size: 14px;
                }
                .header input[type="range"] {
                    width: 200px;
                }
                #gallery {
                    display: grid;
                    grid-template-columns: repeat(auto-fill, minmax(var(--grid-item-size, 100px), 1fr));
                    grid-auto-rows: auto;
                    grid-gap: 10px;
                    grid-auto-flow: dense;
                    padding: 10px;
                }
                .gallery-item {
                    border: 1px solid #ccc;
                    border-radius: 5px;
                    overflow: hidden;
                    position: relative;
                }
                .gallery-item img {
                    width: 100%;
                    height: auto;
                    display: block;
                }
                .gallery-item .title {
                    position: absolute;
                    bottom: 0;
                    width: 100%;
                    background: rgba(0, 0, 0, 0.5);
                    color: white;
                    font-size: 14px;
                    text-align: center;
                    padding: 5px 0;
                }
            </style>
        </head>
        <body>

        <div class="header">
            <input type="text" id="searchBox" placeholder="Search SVGs">
            <input type="range" id="gridSizeSlider" min="100" max="300" value="100">
        </div>
        <div id="gallery"></div>

        <script>
            document.addEventListener('DOMContentLoaded', function () {
                const searchBox = document.getElementById('searchBox');
                const gridSizeSlider = document.getElementById('gridSizeSlider');
                const gallery = document.getElementById('gallery');

                let allSvgFiles = [];

                fetch('/api/svgs')
                    .then(response => response.json())
                    .then(svgFiles => {
                        allSvgFiles = svgFiles;
                        renderGallery(svgFiles);
                    });

                searchBox.addEventListener('input', function() {
                    const query = searchBox.value.toLowerCase();
                    const filteredFiles = allSvgFiles.filter(file => file.toLowerCase().includes(query));
                    renderGallery(filteredFiles);
                });

                gridSizeSlider.addEventListener('input', function() {
                    const gridSize = gridSizeSlider.value;
                    document.documentElement.style.setProperty('--grid-item-size', gridSize + 'px');
                });

                function renderGallery(svgFiles) {
                    gallery.innerHTML = '';
                    svgFiles.forEach(file => {
                        const item = document.createElement('div');
                        item.classList.add('gallery-item');

                        const img = document.createElement('img');
                        img.src = '/svg/' + file;
                        img.alt = file;

                        const title = document.createElement('div');
                        title.classList.add('title');
                        title.textContent = file;

                        item.appendChild(img);
                        item.appendChild(title);
                        gallery.appendChild(item);
                    });
                }
            });
        </script>

        </body>
        </html>
        )";

int main() {
    archanaberry::express::AppWeb app;

    app.get("/", [](boost::asio::ip::tcp::iostream& stream) {
        stream << "HTTP/1.1 200 OK\r\n";
        stream << "Content-Type: text/html\r\n";
        stream << "Connection: close\r\n\r\n";
        stream << html;
        stream.flush();
    });

    app.listen(8080);

    return 0;
}