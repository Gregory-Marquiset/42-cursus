//-------> ./srcs/ScalarConverter.cpp <-------//

#include "../includes/ScalarConverter.hpp"

		//-------> SConv class <-------//

SConv::SConv()
{}

SConv::SConv(const SConv& copy)
{
	*this = copy;
}

SConv&	SConv::operator=(const SConv& other)
{
	if (this != &other)
		return (*this);
	return (*this);
}

SConv::~SConv()
{}

		//-------> Checker utils <-------//

e_type	checkChar(const std::string& s)
{ return (isChar(s) ? CHAR_TYPE : UNKNOWN_TYPE); }

e_type	checkInt(const std::string& s)
{ return (isInt(s) ? INT_TYPE : UNKNOWN_TYPE); }

e_type	checkFloat(const std::string& s)
{ return (isFloat(s) ? FLOAT_TYPE : UNKNOWN_TYPE); }

e_type	checkDouble(const std::string& s)
{ return (isDouble(s) ? DOUBLE_TYPE : UNKNOWN_TYPE); }

t_checker	checkers[] =
{
	{ "char", checkChar, CHAR_TYPE },
	{ "int", checkInt, INT_TYPE },
	{ "float", checkFloat, FLOAT_TYPE },
	{ "double", checkDouble, DOUBLE_TYPE }
};

		//-------> Self methode <-------//

void	SConv::convert(const std::string& literal)
{
	std::string	literalTrimed = trimString(literal);
	if (literalTrimed.empty())
		throw unknownTypeException();
	for (int i = 0; i < 4; i++)
	{
		if (checkers[i].check(literalTrimed) != UNKNOWN_TYPE)
		{
			printConv(literalTrimed, checkers[i].type);
			return ;
		}
	}
	throw unknownTypeException();
}

		//-------> Self Exceptions <-------//

const char*	SConv::unknownTypeException::what() const throw()
{ return ("Unknown type or out of range provided!"); }
