#ifndef MIME_TYPES_HPP
#define MIME_TYPES_HPP

#include <string>
#include <unordered_map>

namespace archanaberry {
    namespace express {

        std::string get_mime_type(const std::string& path);

    } // namespace express
} // namespace archanaberry

#endif // MIME_TYPES_HPP
