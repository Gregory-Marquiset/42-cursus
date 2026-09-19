//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../includes/Span.hpp"

int	main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	try {
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "[Basic Test] Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "[Basic Test] Longest  span: " << sp.longestSpan()  << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error (Basic Test): " << e.what() << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;

	try {
		Span sp_range(5);
		std::vector<int> v;
		for (int i = 1; i <= 5; ++i)
			v.push_back(i * 10);

		sp_range.addNumber(v.begin(), v.end());
		std::cout << "[Range Test] Shortest span: " << sp_range.shortestSpan() << std::endl;
		std::cout << "[Range Test] Longest  span: " << sp_range.longestSpan()  << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error (Range Test): " << e.what() << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;

	try {
		const unsigned int N = 10000;
		Span sp_large(N);
		std::vector<int> big;
		big.reserve(N);
		for (unsigned int i = 0; i < N; ++i)
			big.push_back(std::rand());

		sp_large.addNumber(big.begin(), big.end());
		std::cout << "[Large Test] Shortest span: " << sp_large.shortestSpan() << std::endl;
		std::cout << "[Large Test] Longest  span: " << sp_large.longestSpan()  << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error (Large Test): " << e.what() << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;

	try {
		Span sp_empty(5);
		std::cout << "[Exception Test] shortestSpan on empty: "
				  << sp_empty.shortestSpan() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Expected Exception (NotEnoughNumbers): " << e.what() << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;

	try {
		Span sp_full(3);
		sp_full.addNumber(1);
		sp_full.addNumber(2);
		sp_full.addNumber(3);
		sp_full.addNumber(4);
	}
	catch (const std::exception& e) {
		std::cerr << "Expected Exception (StorageFull): " << e.what() << std::endl;
	}

	return (0);
}