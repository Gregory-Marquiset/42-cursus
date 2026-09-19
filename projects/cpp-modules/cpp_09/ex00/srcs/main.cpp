//-------> ./srcs/Main.cpp <-------//

#include "../includes/BitcoinExchange.hpp"

int	main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::cerr	<< "Error: too many arguments." << std::endl;
		return (1);
	}
	std::string	InputFile;
	if (argc == 2)
		InputFile = static_cast<std::string>(argv[1]);


	try
	{
		BtcExchange	btc("data.csv", InputFile);
	}
	catch(const std::exception& e)
	{
		std::cerr	<< "Error: " << e.what() << std::endl;
	}

	return (0);
}
