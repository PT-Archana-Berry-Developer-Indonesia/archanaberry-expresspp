#include "html2cpp.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

Html2Cpp::Html2Cpp(const std::string& inputFile, const std::string& outputFile)
    : inputFile_(inputFile), outputFile_(outputFile) {}

void Html2Cpp::convert() const {
    std::string content = readFile();
    std::string escapedContent = escapeString(content);
    writeFile(escapedContent);
}

std::string Html2Cpp::readFile() const {
    std::ifstream inFile(inputFile_);
    if (!inFile) {
        throw std::runtime_error("Could not open input file: " + inputFile_);
    }

    std::ostringstream sstr;
    sstr << inFile.rdbuf();
    return sstr.str();
}

void Html2Cpp::writeFile(const std::string& content) const {
    std::ofstream outFile(outputFile_);
    if (!outFile) {
        throw std::runtime_error("Could not open output file: " + outputFile_);
    }

    outFile << "#include <string>\n\n";
    outFile << "const std::string html_content = R\"(" << content << ")\";\n";
}

std::string Html2Cpp::escapeString(const std::string& input) const {
    std::ostringstream escaped;
    escaped << std::quoted(input, '\"', '\\');
    return escaped.str();
}
