//-------> ./srcs/Intern.cpp <-------//

#include "../includes/Intern.hpp"

		//-------> FormTable struct <-------//

AForm*	createPPForm(const std::string& target)
{
	return (new PPForm(target));
}

AForm*	createRRForm(const std::string& target)
{
	return (new RRForm(target));
}

AForm*	createSCForm(const std::string& target)
{
	return (new SCForm(target));
}

const FormTable	Intern::_formTable[3] =
{
	{"presidential pardon", createPPForm},
	{"robotomy request", createRRForm},
	{"shrubbery creation", createSCForm}
};

		//-------> Intern class <-------//

Intern::Intern()
{}

Intern::Intern(const Intern& copy)
{
	*this = copy;
}

Intern&	Intern::operator=(const Intern& other)
{
	if (this != &other)
		return (*this);
	return (*this);
}

Intern::~Intern()
{}

		//-------> Self methode <-------//

AForm*	Intern::makeForm(std::string form, std::string target)
{
	for (int i = 0; i < 3; i++)
	{
		if (_formTable[i].name == form)
		{
			std::cout	<< "Intern creates "
						<< form
						<< std::endl;
			return (_formTable[i].create(target));
		}
	}
	throw unknownFormException();
}

		//-------> Self Exceptions <-------//

const char*	Intern::unknownFormException::what() const throw()
{
	return ("Unkown form");
}