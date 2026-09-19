//-------> ./includes/RPN.hpp <-------//

#ifndef RPN_CPP
#define RPN_CPP

#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

class	RPN
{
	private:
		std::stack< int, std::list<int> > _Pile;
		void	ResolveEquation(const std::string& Equation);
	public:
		RPN();
		RPN(const RPN& Other);
		RPN(const std::string& Equation);
		~RPN();
		RPN&    operator=(const RPN& Other);

		class	NoEquationException : public std::exception
		{
			const char*	what() const throw();
		};
		class	NumberNotInRangeException : public std::exception
		{
			const char*	what() const throw();
		};
		class	NoOperandsException : public std::exception
		{
			const char*	what() const throw();
		};
		class	DivisionByZeroException : public std::exception
		{
			const char*	what() const throw();
		};
		class	InvalideTokenException : public std::exception
		{
			const char*	what() const throw();
		};
		class	InvalideRPNException : public std::exception
		{
			const char*	what() const throw();
		};
};

#endif //	RPN_CPP
