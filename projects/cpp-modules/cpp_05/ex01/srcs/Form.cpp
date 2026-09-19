//-------> ./srcs/Form.cpp <-------//

#include "../includes/Form.hpp"
# include "../includes/Bureaucrat.hpp"

Form::Form() :
	_name("Form 00"), _signed(0), _signGrade(150), _execGrade(150)
{}

Form::Form(const Form& copy)
{
	*this = copy;
}

Form&	Form::operator=(const Form& other)
{
	if (this != &other)
	{
		_name = other.getName();
		_signed = other.getSigned();
		_signGrade = other.getSignGrade();
		_execGrade = other.getExecGrade();
	}
	return (*this);
}

Form::~Form()
{}

Form::Form(std::string name, int signGrade, int execGrade) :
	_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

		//-------> Self methode <-------//
const std::string	Form::getName() const
{
	return (_name);
}

bool				Form::getSigned() const
{
	return (_signed);
}

int					Form::getSignGrade() const
{
	return (_signGrade);
}

int					Form::getExecGrade() const
{
	return (_execGrade);
}

void				Form::beSign(const Bureaucrat& b)
{
	if (_signed)
		return ;
	if (b.getGrade() > getSignGrade())
		throw	GradeTooLowException();
	_signed = true;
}

		//-------> Self Exceptions <-------//

const char*	Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char*	Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

		//-------> Other <-------//

std::ostream&	operator<<(std::ostream& os, const Form& f)
{
	os	<< "Form name : "	<< f.getName()		<< std::endl
		<< "Signed : "		<< f.getSigned()	<< std::endl
		<< "SignGrade : "	<< f.getSignGrade()	<< std::endl
		<< "ExecGrade : "	<< f.getExecGrade();
	return (os);
}