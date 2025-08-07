#include "Base.hpp"
#include <iostream>

int main() {
    std::cout << "=== Testing generated object ===" << std::endl;
    Base* basePtr = Base::generate();
    std::cout << "Pointer identification: ";
    Base::identify(basePtr);
    std::cout << "Reference identification: ";
    Base::identify(*basePtr);
    delete basePtr;

    std::cout << "\n=== Testing pure Base object ===" << std::endl;
    Base* pureBase = new Base();
    std::cout << "Pointer identification: ";
    Base::identify(pureBase);
    std::cout << "Reference identification: ";
    Base::identify(*pureBase);
    delete pureBase;

    return 0;
}
