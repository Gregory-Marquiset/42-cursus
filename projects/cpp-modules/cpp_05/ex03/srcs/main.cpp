//-------> ./srcs/Main.cpp <-------//

# include "../includes/Bureaucrat.hpp"
# include "../includes/Intern.hpp"

int	main()
{
	srand(time(NULL));
	try
	{
		Bureaucrat	b("greg", 3);
		Intern	i;
		AForm*	f;
		f = i.makeForm("presidential pardon", "bob");
		b.signForm(*f);
		b.executeForm(*f);
		delete f;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ( 0 );
}
