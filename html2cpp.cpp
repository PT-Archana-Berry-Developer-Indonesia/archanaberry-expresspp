#include "libhtml2cpp/html2cpp.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.html> -o <output.htmlc>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string option = argv[2];
    std::string outputFile = argv[3];

    if (option != "-o") {
        std::cerr << "Invalid option: " << option << "\n";
        return 1;
    }

    try {
        Html2Cpp converter(inputFile, outputFile);
        converter.convert();
        std::cout << "Conversion successful. Output written to " << outputFile << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
