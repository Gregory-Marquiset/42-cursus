# include <../includes/Zombie.hpp>

Zombie*	zombieHorde( int N, std::string name )
{
	if ( N <= 0 )
		return (NULL);
	
	Zombie*	z = NULL;
	try
	{
		z = new ( std::nothrow ) Zombie[N];
	}
	catch (const std::bad_alloc& error)
	{
		std::cerr << "Error : echec allocation -> " << error.what() << std::endl;
		return (NULL);
    }
	if ( !z )
	{
		std::cerr << "Error : allocation imposible for the zombies horde!" << std::endl;
		return (NULL);
	}

	for ( int i = 0 ;i < N ;i++ )
		z[i].setParams( name ,i );
	return (z);
}