#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

Base::~Base()
{
	std::cout << "Base destructor called\n";
}

Base *Base::generate()
{
	std::srand(static_cast<unsigned int>(time(0)));
	int choice = rand() % 3;
	if (choice == 0) {
		return new A();
	}
	if (choice == 1) {
		return new B();
	}
	return new C();
	// types = [

	// ]
}

void Base::identify(Base *basePtr)
{
	if (dynamic_cast<A *>(basePtr))
	{
		std::cout << "A\n";
	}
	else if (dynamic_cast<B *>(basePtr))
	{
		std::cout << "B\n";
	}
	else if (dynamic_cast<C *>(basePtr))
	{
		std::cout << "C\n";
	}
}

void Base::identify(Base &baseRef)
{
	try
	{
		(void)dynamic_cast<A &>(baseRef);
		std::cout << "A\n";
		return;
	}
	catch (...)
	{
	}

	try
	{
		(void)dynamic_cast<B &>(baseRef);
		std::cout << "B\n";
		return;
	}
	catch (...)
	{
	}

	try
	{
		(void)dynamic_cast<C &>(baseRef);
		std::cout << "C\n";
		return;
	}
	catch (...)
	{
	}
}
