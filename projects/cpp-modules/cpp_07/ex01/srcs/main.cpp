//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include "../includes/Iter.hpp"
#include "../includes/Function.hpp"

int main()
{
	int tab[] = { 1, 2, 3, 4 };
	std::cout << "Original:" << std::endl;
	iter(tab, 4, printElem);

	iter(tab, 4, increment);
	std::cout << "Incremented:" << std::endl;
	iter(tab, 4, printElem);

	std::string strs[] = { "bonjour", "42", "iter" };
	std::cout << "Strings:" << std::endl;
	iter(strs, 3, printElem);

	return (0);
}