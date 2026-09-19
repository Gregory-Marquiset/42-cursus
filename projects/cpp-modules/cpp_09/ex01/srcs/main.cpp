//-------> ./srcs/Main.cpp <-------//

#include "../includes/RPN.hpp"

int	main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::cerr	<< "Error: too many arguments." << std::endl;
		return (1);
	}

	std::string	Equation;
	if (argc == 1)
		Equation = "";
	else
		Equation = argv[1];
	try
	{
		RPN	Solver(Equation);
	}
	catch (const std::exception& e)
	{
		std::cerr	<< "Error: " << e.what() << std::endl;
	}

	return (0);
}
