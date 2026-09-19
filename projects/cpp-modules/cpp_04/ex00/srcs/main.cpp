//-------> ./srcs.Main.cpp <-------//

# include "../includes/Cat.hpp"
# include "../includes/Dog.hpp"

int	main()
{
	Animal	h;
	const Animal*	j = new Dog();
	const Animal*	i = new Cat();

	std::cout	<< h.getType() << std::endl;
	h.makeSound();
	std::cout	<< j->getType() << std::endl;
	j->makeSound();
	std::cout	<< i->getType() << std::endl;
	i->makeSound();

	delete j;
	delete i;
	return ( 0 );
}
