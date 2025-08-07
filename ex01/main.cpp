#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>
#include <cassert>

int main(void)
{
	Data raw;
	raw.value = 12345;
	raw.str = "test data";

	std::cout << "[Original data]\n";
	std::cout << "value: " << raw.value << "\n";
	std::cout << "str: " << raw.str << "\n";

	uintptr_t ptr = Serializer::serialize(&raw);
	Data *rev = Serializer::deserialize(ptr);

	std::cout << "[Deserialized data]\n";
	std::cout << "value: " << rev->value << "\n";
	std::cout << "str: " << rev->str << "\n";

	// Assert that the original pointer and deserialized pointer are the same
	assert(rev == &raw);
	std::cout << "Pointer integrity test passed\n";

	// Assert that the data values match
	assert(rev->value == raw.value);
	assert(rev->str == raw.str);
	std::cout << "Data integrity test passed\n";

	return 0;
}
