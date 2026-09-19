//-------> ./srcs/Main.cpp <-------//

# include "../includes/Bureaucrat.hpp"

int	main()
{
	try
	{
		Bureaucrat	b("bob", 150);
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << b << std::endl;

		Form	f("form 01", 148, 150);
		b.signForm(f);
		b.incrementGrade();
		std::cout << b << std::endl;
		b.signForm(f);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ( 0 );
}
