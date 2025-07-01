#include "Serializer.hpp"
#include <iostream>

// Default constructor
Serializer::Serializer(void)
{
    std::cout << "Default constructor called\n";
}

// Copy constructor
Serializer::Serializer(const Serializer &other)
{
    std::cout << "Copy constructor called\n";
    (void) other;
}

// Assignment operator overload
Serializer &Serializer::operator=(const Serializer &other)
{
    std::cout << "Assignment operator called\n";
    if (this != &other)
    {
        (void) other;
    }
    return (*this);
}

// Destructor
Serializer::~Serializer(void)
{
    std::cout << "Destructor called\n";
}

uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data *>(raw);
}
