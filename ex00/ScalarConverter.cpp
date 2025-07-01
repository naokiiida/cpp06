#include "ScalarConverter.hpp"
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Default constructor
ScalarConverter::ScalarConverter(void)
{
	std::cout << "Default constructor called\n";
}

// Copy constructor
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	std::cout << "Copy constructor called\n";
	(void)other;
}

// Assignment operator overload
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	std::cout << "Assignment operator called\n";
	if (this != &other)
	{
		(void)other;
	}
	return (*this);
}

// Destructor
ScalarConverter::~ScalarConverter(void)
{
	std::cout << "Destructor called\n";
}

// Helper function to check if conversion is possible and safe
bool ScalarConverter::isConversionSafe(long value, LiteralType targetType)
{
	switch (targetType)
	{
	case CHAR:
		return (value >= CHAR_MIN && value <= CHAR_MAX);
	case INT:
		return (value >= INT_MIN && value <= INT_MAX);
	default:
		return true;
	}
}

// Helper function to handle special float/double values
bool ScalarConverter::isSpecialValue(const std::string &literal)
{
	return (literal == "nan" || literal == "nanf" || literal == "+inf" || literal == "+inff" || literal == "-inf" || literal == "-inff");
}

// Helper function to print conversion results safely
void ScalarConverter::printConversions(char c, int i, float f, double d, bool charPossible, bool intPossible)
{
	// Print char
	if (charPossible)
	{
		if (c >= 32 && c <= 126)
		{
			std::cout << "char: '" << c << "'\n";
		}
		else
		{
			std::cout << "char: Non displayable\n";
		}
	}
	else
	{
		std::cout << "char: impossible\n";
	}

	// Print int
	if (intPossible)
	{
		std::cout << "int: " << i << "\n";
	}
	else
	{
		std::cout << "int: impossible\n";
	}

	// Print float
	if (f != f)
	{ // NaN check
		std::cout << "float: nanf\n";
	}
	else if (f == static_cast<int>(f))
	{
		std::cout << "float: " << f << ".0f\n";
	}
	else
	{
		std::cout << "float: " << f << "f\n";
	}

	// Print double
	if (d != d)
	{ // NaN check
		std::cout << "double: nan\n";
	}
	else if (d == static_cast<int>(d))
	{
		std::cout << "double: " << d << ".0\n";
	}
	else
	{
		std::cout << "double: " << d << "\n";
	}
}

bool ScalarConverter::isNum(const std::string &literal)
{
	int signBit = 0;
	if (literal[0] == '-')
	{
		signBit = 1;
	}
	for (size_t i = signBit; i < literal.length(); i++)
	{
		if (std::isdigit(literal[i]) == 0)
		{
			return false;
		}
	}
	return literal.length() != 1;
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	if (isSpecialValue(literal))
	{
		return (literal == "nanf" || literal == "+inff" || literal == "-inff");
	}

	int signBit = 0;
	int dotCount = 0;
	size_t floatLength = literal.length();

	if (literal[0] == '-' || literal[0] == '+')
	{
		signBit = 1;
	}
	if (floatLength > 1 && literal[floatLength - 1] == 'f')
	{
		floatLength--;
	}
	else
	{
		return false; // Float must end with 'f'
	}

	for (size_t i = signBit; i < floatLength; i++)
	{
		if (std::isdigit(literal[i]) == 0)
		{
			if (literal[i] == '.' && dotCount == 0)
			{
				dotCount++;
			}
			else
			{
				return false;
			}
		}
	}
	return floatLength > signBit && dotCount == 1;
}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string &literal)
{
	if (literal.empty())
	{
		return INVALID;
	}
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
	{
		return DOUBLE;
	}
	if (literal.length() == 1 && std::isdigit(literal[0]) == 0)
	{
		return CHAR;
	}
	if (isFloat(literal))
	{
		return FLOAT;
	}
	if (isNum(literal))
	{
		return INT;
	}
	if (literal.find('.') != std::string::npos)
	{
		return DOUBLE;
	}

	return INVALID;
}

// Helper function to safely convert string to long
long ScalarConverter::getLong(const std::string &literal, bool &success)
{
	errno = 0;
	char *endptr = NULL;
	long value = std::strtol(literal.c_str(), &endptr, 10);

	success = (errno == 0 && *endptr == '\0' && endptr != literal.c_str());
	return value;
}

void ScalarConverter::convert(const std::string &literal)
{
	LiteralType type = detectType(literal);

	if (type == INVALID)
	{
		std::cout << "Error: Invalid literal\n";
		return;
	}

	char charVal = 0;
	int intVal = 0;
	float floatVal = 0.0F;
	double doubleVal = 0.0;
	bool charPossible = true;
	bool intPossible = true;

	switch (type)
	{
	case CHAR:
	{
		charVal = literal[0];
		intVal = static_cast<int>(charVal);
		floatVal = static_cast<float>(charVal);
		doubleVal = static_cast<double>(charVal);
		break;
	}
	case INT:
	{
		bool success = false;
		long longVal = getLong(literal, success);

		if (!success)
		{
			charPossible = false;
			intPossible = false;
		}
		else
		{
			charPossible = isConversionSafe(longVal, CHAR);
			intPossible = isConversionSafe(longVal, INT);

			if (charPossible)
			{
				charVal = static_cast<char>(longVal);
			}
			if (intPossible)
			{
				intVal = static_cast<int>(longVal);
			}
		}
		floatVal = static_cast<float>(longVal);
		doubleVal = static_cast<double>(longVal);
		break;
	}
	case FLOAT:
	{
		std::string temp = literal;
		if (temp[temp.length() - 1] == 'f')
		{
			temp = temp.substr(0, temp.length() - 1);
		}

		errno = 0;
		floatVal = std::strtof(temp.c_str(), NULL);
		doubleVal = static_cast<double>(floatVal);

		charPossible = false;
		intPossible = false;
		break;
	}
	case DOUBLE:
	{
		errno = 0;
		doubleVal = std::strtod(literal.c_str(), NULL);
		floatVal = static_cast<float>(doubleVal);

		charPossible = false;
		intPossible = false;
		break;
	}

	default:
		return;
	}

	printConversions(charVal, intVal, floatVal, doubleVal, charPossible, intPossible);
}
