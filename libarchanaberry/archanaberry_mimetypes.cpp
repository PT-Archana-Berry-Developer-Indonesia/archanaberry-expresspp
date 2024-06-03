#include "archanaberry_mimetypes.hpp"

namespace archanaberry {
    namespace express {

        std::string get_mime_type(const std::string& path) {
            static std::unordered_map<std::string, std::string> mime_types = {
                {".html", "text/html"},
                {".htm", "text/html"},
                {".css", "text/css"},
                {".js", "application/javascript"},
                {".json", "application/json"},
                {".png", "image/png"},
                {".jpg", "image/jpeg"},
                {".jpeg", "image/jpeg"},
                {".gif", "image/gif"},
                {".svg", "image/svg+xml"},
                {".ico", "image/x-icon"},
                {".wav", "audio/wav"},
                {".mp3", "audio/mpeg"},
                {".mp4", "video/mp4"},
                {".ogg", "audio/ogg"},
                {".ogv", "video/ogg"},
                {".pdf", "application/pdf"},
                {".txt", "text/plain"},
                // Add more MIME types as needed
            };

            std::size_t dot_pos = path.find_last_of(".");
            if (dot_pos != std::string::npos) {
                std::string ext = path.substr(dot_pos);
                if (mime_types.count(ext)) {
                    return mime_types[ext];
                }
            }
            return "application/octet-stream";
        }

    } // namespace express
} // namespace archanaberry
