# include <../includes/Zombie.hpp>

int	main( int argc, char **argv )
{
	if (argc != 3)
	{
		std::cerr << "Error : bad arguments format!" << std::endl;
		return (1);
	}

	int		n = atoi(argv[1]);
	if ( n <= 0 )
	{
		std::cerr << "Error : argv[1] invalide" << std::endl;
		return (2);
	}
	Zombie*	z = zombieHorde( n, argv[2] );
	if (!z)
		return (3);

	for (int i = 0; i < n ;i++)
		z[i].announce();
	std::cout << std::endl;
	delete[] z;
	return (0);
}