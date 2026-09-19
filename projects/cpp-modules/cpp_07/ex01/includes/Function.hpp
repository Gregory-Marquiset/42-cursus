#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>

template<typename T>
void printElem(const T& elem)
{
	std::cout << elem << std::endl;
}

template<typename T>
void increment(T& elem)
{
	++elem;
}

#endif // FUNCTION_HPP