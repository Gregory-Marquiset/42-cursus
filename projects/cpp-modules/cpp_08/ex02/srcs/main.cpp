//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include "MutantStack.hpp"

int	main()
{
	MutantStack<int> mstack;

	// test simple
	mstack.push(5);
	mstack.push(17);
	std::cout << "[Simple] top(): " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "[Simple] size(): " << mstack.size() << std::endl;

	// remplissage supplémentaire
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	// itération avant
	std::cout << "[Iteration forward] ";
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// itération arrière
	std::cout << "[Iteration backward] ";
	for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;

	// compatibilité avec std::stack
	std::stack<int> s(mstack);
	(void)s; // juste pour montrer que la conversion compile

	return 0;
}