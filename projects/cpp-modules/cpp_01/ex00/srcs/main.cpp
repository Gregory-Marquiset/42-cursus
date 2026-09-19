# include "../includes/Zombie.hpp"

int	main( void )
{
	Zombie*	z = newZombie( "Heapz" );
	z->announce();
	delete z;
	randomChump( "Stackz" );
	return (0);
}