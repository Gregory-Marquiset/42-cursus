//-------> ./srcs/main.cpp <-------//

#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"

int	main()
{
	std::cout << "\n--- Création du tableau d'animaux ---\n" << std::endl;
	const int N = 4;
	Animal* animals[N];

	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	std::cout << "\n--- Ajout d'idées dans les cerveaux ---\n" << std::endl;
	for (int i = 0; i < N; i++)
	{
		if (Dog* d = dynamic_cast<Dog*>(animals[i]))
			d->getBrain()->setIdea(0, "Protéger la maison");
		else if (Cat* c = dynamic_cast<Cat*>(animals[i]))
			c->getBrain()->setIdea(0, "Voler du poisson");

		std::cout << animals[i]->getType() << " pense à : ";
		if (Dog* d = dynamic_cast<Dog*>(animals[i]))
			std::cout << d->getBrain()->getIdea(0) << std::endl;
		else if (Cat* c = dynamic_cast<Cat*>(animals[i]))
			std::cout << c->getBrain()->getIdea(0) << std::endl;
	}

	std::cout << "\n--- Destruction du tableau d'animaux ---\n" << std::endl;
	for (int i = 0; i < N; i++)
		delete animals[i];

	std::cout << "\n--- Test de deep copy ---\n" << std::endl;

	Cat cat1;
	cat1.getBrain()->setIdea(0, "Dormir");
	cat1.getBrain()->setIdea(1, "Chasser les souris");

	Cat cat2(cat1);

	std::cout << "cat1 Brain[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
	std::cout << "cat2 Brain[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

	cat1.getBrain()->setIdea(0, "Manger");

	std::cout << "\nAprès modification de cat1 :" << std::endl;
	std::cout << "cat1 Brain[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
	std::cout << "cat2 Brain[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

	std::cout << "\n--- Fin du programme ---\n" << std::endl;
	return ( 0 );
}
