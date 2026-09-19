//-------> ./srcs/Main.cpp <-------//

# include "../includes/ScalarConverter.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr	<< "Usage ./convert <literal>!"
					<< std::endl;
		return (1);
	}
	try
	{
		SConv::convert(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr	<< "Error: "
					<< e.what()
					<< std::endl;
		return (2);
	}
	return (0);
}
