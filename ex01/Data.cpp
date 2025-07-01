#include "Data.hpp"
#include <iostream>

// Default constructor
Data::Data(void) : value(42), str("default data")
{
    std::cout << "Default constructor called\n";
}

// Copy constructor
Data::Data(const Data &other) : value(other.value), str(other.str)
{
    std::cout << "Copy constructor called\n";
}

// Assignment operator overload
Data &Data::operator=(const Data &other)
{
    std::cout << "Assignment operator called\n";
    if (this != &other)
    {
        value = other.value;
        str = other.str;
    }
    return (*this);
}

// Destructor
Data::~Data(void)
{
    std::cout << "Destructor called\n";
}

