#include "../includes/Harl.hpp"

int	main( int argc, char** argv )
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <log level>" << std::endl;
		return (1);
	}
	Harl		h;
	std::string	level = argv[1];
	h.complain( level );
	return (0);
}