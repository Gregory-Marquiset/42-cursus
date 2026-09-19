#include "../includes/Harl.hpp"

int	main( void )
{
	Harl		h;
	std::string	level;

	std::cout << "Enter a complaint level (DEBUG, INFO, WARNING, ERROR): ";
	std::cin >> level;
	h.complain( level );
	return (0);
}