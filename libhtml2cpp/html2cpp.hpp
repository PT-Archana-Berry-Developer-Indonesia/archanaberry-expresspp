#ifndef HTML2CPP_HPP
#define HTML2CPP_HPP

#include <string>

class Html2Cpp {
public:
    Html2Cpp(const std::string& inputFile, const std::string& outputFile);
    void convert() const;

private:
    std::string inputFile_;
    std::string outputFile_;

    std::string readFile() const;
    void writeFile(const std::string& content) const;
    std::string escapeString(const std::string& input) const;
};

#endif // HTML2CPP_HPP
