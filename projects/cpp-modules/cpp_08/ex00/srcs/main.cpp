//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include <vector>
#include <list>
#include "../includes/easyfind.hpp"

int	main()
{
	try {
		std::vector<int> vec;
		for (int i = 0; i < 10; ++i)
			vec.push_back(i);

		std::vector<int>::iterator it = easyfind(vec, 5);
		std::cout << "Found in vector: " << *it << std::endl;

		std::list<int> lst;
		lst.push_back(1);
		lst.push_back(3);
		lst.push_back(7);

		std::list<int>::iterator it2 = easyfind(lst, 3);
		std::cout << "Found in list: " << *it2 << std::endl;

		easyfind(vec, 42);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
