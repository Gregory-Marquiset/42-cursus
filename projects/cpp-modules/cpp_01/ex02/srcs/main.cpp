# include <iostream>
# include <string>

int	main( void )
{
	std::string		str = "HI THIS IS BRAIN";
	std::string*	strptr = &str;
	std::string&	strref = str;

	std::cout << "Adress of str: " << &str << std::endl;
	std::cout << "Adress of strptr: " << strptr << std::endl;
	std::cout << "Adress of strref: " << &strref << std::endl;
	std::cout << std::endl;
	std::cout << "Value of str: " << str << std::endl;
	std::cout << "Value of strptr: " << *strptr << std::endl;
	std::cout << "Value of strref: " << strref << std::endl;
	return (0);
}