//-------> ./srcs/RPN.cpp <-------//

#include "../includes/RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN& Other)
{
	*this = Other;
}

RPN::RPN(const std::string& Equation)
{
	if (Equation.empty())
		throw(NoEquationException());
	ResolveEquation(Equation);
}

RPN::~RPN()
{}

RPN&	RPN::operator=(const RPN& Other)
{
	if (this != &Other)
		_Pile = Other._Pile;
	return (*this);
}

const char*	RPN::NoEquationException::what() const throw()
{
	return ("no equation to solve.");
}

const char*	RPN::NumberNotInRangeException::what() const throw()
{
	return ("Positive integer less than 10 required.");
}

const char*	RPN::NoOperandsException::what() const throw()
{
	return ("not enough operands to apply the operator.");
}

const char*	RPN::DivisionByZeroException::what() const throw()
{
	return (" division by zero.");
}

const char*	RPN::InvalideTokenException::what() const throw()
{
	return ("invalide token.");
}

const char*	RPN::InvalideRPNException::what() const throw()
{
	return ("invalide RPN expression.");
}

void	RPN::ResolveEquation(const std::string& Equation)
{
	std::istringstream	Iss(Equation);
	std::string			Token;
	int					A, B, Result, Num;

	while (Iss >> Token)
	{
		if (Token == "+" || Token == "-" || Token == "/" || Token == "*")
		{
			if (_Pile.size() < 2)
				throw(NoOperandsException());
			
			A = _Pile.top();
			_Pile.pop();
			B = _Pile.top();
			_Pile.pop();
			if (Token == "+")
				Result = B + A;
			else if (Token == "-")
				Result = B - A;
			else if (Token == "*")
				Result = B * A;
			else
			{
				if (A == 0)
					throw(DivisionByZeroException());
				Result = B / A;
			}
			_Pile.push(Result);
		}
		else
		{
			std::istringstream	conv(Token);
			if(!(conv >> Num) || !(conv.eof()))
				throw(InvalideTokenException());
			if (Num >= 10 || Num < 0)
				throw(NumberNotInRangeException());
			_Pile.push(Num);
		}
	}
	if (_Pile.size() != 1)
		throw(InvalideRPNException());
	std::cout	<< _Pile.top() << std::endl;
}