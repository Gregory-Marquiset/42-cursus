//-------> ./includes/ScalarConverter.hpp <-------//

# ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include "check.hpp"
#include "display.hpp"

#include <cctype>

		//-------> Checker utils <-------//

typedef	e_type	(*typeChecker)(const std::string&);

typedef struct	s_checker
{
	const char*	name;
	typeChecker	check;
	e_type		type;
}	t_checker;

		//-------> SConv class <-------//

class	SConv
{
	private :
		SConv();
		SConv(const SConv& copy);
		~SConv();
		SConv&	operator=(const SConv& other);
		static const t_checker	_checkerTable[4];
	public :
		//-------> Self methode <-------//
		static void	convert(const std::string& literal);

		//-------> Self Exceptions <-------//
		class	unknownTypeException : public std::exception
		{
			public :
				const char*	what() const throw();
		};
};

#endif //	SCALARCONVERTER_HPP