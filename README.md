# ARCHANABERRY EXPRESS++

![Archana Berry Express++](archanaberry/banner.png)

## Deskripsi
ArchanaBerry Express adalah library web minimalis tetapi fitur juga lengkap dan berbasis C++ yang mirip dengan Express.js di Node.js. Library ini memungkinkan Anda untuk membuat server web dengan mudah, menangani rute, dan mendukung multithreading. Dengan menggunakan Boost.Beast dan Boost.Asio, ArchanaBerry Express menawarkan kinerja yang tinggi dan fleksibilitas untuk pengembangan aplikasi web.

![Archana Berry dan Archie Wheatgrace](archanaberry/berryexpress.png)

## Informasi
- **Penulis:** Archana Berry
- **Versi:** 1.0.0
- **Lisensi:** MIT
- **Bahasa:** C++
- **Dependencies:**
  - Boost.Beast
  - Boost.Asio
  - Boost.System
  - Boost.Thread

## Cara Pakai
1. **Instalasi Boost Library**
   Pastikan Boost library yang mencakup Boost.Beast dan Boost.Asio sudah terinstal di sistem Anda. Anda dapat menginstal Boost library menggunakan manajer paket sistem atau mengunduh dan mengkompilasinya dari situs resmi Boost.

2. **Kompilasi dan Menjalankan Server**
   Buat file `main.cpp`, `archanaberry.hpp`, dan `archanaberry.cpp` dengan konten seperti yang dijelaskan sebelumnya. Kemudian kompilasi dengan perintah berikut (contoh untuk g++):

   ```bash
   g++ -o nama_app nama_webbapp.cpp berry_express.cpp -lboost_system -lboost_thread -lpthread
   ```

   Jalankan server dengan perintah:

   ```bash
   ./nama_app
   ```

3. **Membuat Rute**
   Anda dapat membuat rute untuk menangani permintaan HTTP seperti contoh berikut:

```cpp
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
```

## Screenshot
![Screenshot 1](https://via.placeholder.com/800x400.png?text=Screenshot+1)
*Gambar 1: Halaman Utama*

![Screenshot 2](https://via.placeholder.com/800x400.png?text=Screenshot+2)
*Gambar 2: Konsol JavaScript*

![Screenshot 3](https://via.placeholder.com/800x400.png?text=Screenshot+3)
*Gambar 3: Struktur Proyek*

## Status Fitur yang Akan Dikembangkan

* ✅ Selesai
* ❎ Belum diperbaiki

| Fitur                      | Status          |
|----------------------------|-----------------|
| Routing dasar              | ✅ |
| Dukungan multithreading    | ✅ |
| Dekomposisi HTML/CSS/JS    | ✅ |
| Dukungan file statis semua format | ✅ |
| Middleware                 | Dalam Pengembangan |
| Pengelolaan Static Files   | Dalam Pengembangan |
| Template Engine            | ❎ |
| Pengelolaan Session/Cookie | ❎ |
| Dokumentasi Lengkap        | ❎ |
| Contoh Proyek              | ❎ |

## Kontribusi
Kami sangat terbuka untuk kontribusi dari komunitas. Silakan buat pull request atau buka isu baru di repositori GitHub kami jika Anda menemukan bug atau memiliki fitur yang ingin ditambahkan.

## Lisensi
Proyek ini dilisensikan di bawah lisensi MIT. Lihat file [LICENSE](LICENSE) untuk informasi lebih lanjut.
