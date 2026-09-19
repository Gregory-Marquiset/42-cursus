//-------> ./srcs/Main.cpp <-------//

# include "../includes/Bureaucrat.hpp"

int	main()
{
	srand(time(NULL));
	try
	{
		Bureaucrat b("bob", 6);
		AForm*	f = new SCForm("home");
		std::cout << *f << std::endl;
		b.signForm(*f);
		b.incrementGrade();
		b.executeForm(*f);
		delete f;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ( 0 );
}
