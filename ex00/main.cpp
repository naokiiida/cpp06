#include "ScalarConverter.hpp"
#include <cctype>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // std::cerr << "Usage: ./convert <input>\n";
        // return 1;

        ScalarConverter::convert("c");
        std::cout << "===\n";
        ScalarConverter::convert("0");
        std::cout << "===\n";
        ScalarConverter::convert("42");
        std::cout << "===\n";
        ScalarConverter::convert("-42");
        std::cout << "===\n";
        ScalarConverter::convert("-2147483649");
        std::cout << "===\n";
        ScalarConverter::convert("42.42F");
        std::cout << "===\n";
        ScalarConverter::convert("84.84");
        std::cout << "===\n";
        return 0;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}
