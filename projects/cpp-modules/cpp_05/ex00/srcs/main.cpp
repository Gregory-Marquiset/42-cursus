//-------> ./srcs/Main.cpp <-------//

# include "../includes/Bureaucrat.hpp"

int	main()
{
	try
	{
		Bureaucrat	b("bob", 2);
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << b << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception catch: " << e.what() << std::endl;
	}
	try
	{
		Bureaucrat	b("bob", 149);
		std::cout << b << std::endl;
		b.decrementGrade();
		std::cout << b << std::endl;
		b.decrementGrade();
		std::cout << b << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception catch: " << e.what() << std::endl;
	}
	return ( 0 );
}
