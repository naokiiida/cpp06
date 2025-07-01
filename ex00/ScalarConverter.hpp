#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP
#include <string>

class ScalarConverter
{
    public:
        static void convert(const std::string &literal);
    private:
        ScalarConverter(void);
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter &operator=(const ScalarConverter &other);
        ~ScalarConverter();
        enum LiteralType {
            INVALID,
            CHAR,
            INT,
            FLOAT,
            DOUBLE
        };
        static LiteralType detectType(const std::string &literal);
        static bool isNum(const std::string &literal);
        static bool isFloat(const std::string &literal);
        static bool isConversionSafe(long value, LiteralType targetType);
        static bool isSpecialValue(const std::string &literal);
        static long getLong(const std::string &literal, bool &success);
        static void printConversions(char c, int i, float f, double d,  bool charPossible, bool intPossible);
};

#endif
