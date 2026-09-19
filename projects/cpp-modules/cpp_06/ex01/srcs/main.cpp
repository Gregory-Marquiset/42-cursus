//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include "../includes/Serializer.hpp"

int main()
{
	Data		original;
	original.info = "Hello, World!";
	original.value = 42;

	uintptr_t	raw = Serializer::serialize(&original);
	Data*		copy = Serializer::deserialize(raw);

	std::cout << "Original address: " << &original << std::endl;
	std::cout << "Serialized (uintptr_t): " << raw << std::endl;
	std::cout << "Deserialized address: " << copy << std::endl;

	std::cout << "copy->info: " << copy->info << std::endl;
	std::cout << "copy->value: " << copy->value << std::endl;

	return (0);
}
