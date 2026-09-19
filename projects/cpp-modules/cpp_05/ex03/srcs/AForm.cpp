//-------> ./srcs/AForm.cpp <-------//

#include "../includes/AForm.hpp"
# include "../includes/Bureaucrat.hpp"

AForm::AForm() :
	_name("AForm 00"), _signed(0), _signGrade(150), _execGrade(150)
{}

AForm::AForm(const AForm& copy)
{
	*this = copy;
}

AForm&	AForm::operator=(const AForm& other)
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

AForm::~AForm()
{}

AForm::AForm(std::string name, int signGrade, int execGrade) :
	_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

		//-------> Self methode <-------//
const std::string	AForm::getName() const
{
	return (_name);
}

bool				AForm::getSigned() const
{
	return (_signed);
}

int					AForm::getSignGrade() const
{
	return (_signGrade);
}

int					AForm::getExecGrade() const
{
	return (_execGrade);
}

void				AForm::setName(std::string name)
{
	_name = name;
}

void				AForm::setSigned(bool b)
{
	_signed = b;
}

void				AForm::setSignGrade(int signGrade)
{
	_signGrade = signGrade;
}

void				AForm::setExecGrade(int execGrade)
{
	_execGrade = execGrade;
}

void				AForm::beSign(const Bureaucrat& b)
{
	if (_signed)
		return ;
	if (b.getGrade() > getSignGrade())
		throw	GradeTooLowException();
	_signed = true;
}

void		AForm::execute(const Bureaucrat& b) const
{
	if (!_signed)
		throw formNotSignedException();
	if (b.getGrade() > getExecGrade())
		throw GradeTooLowForExecuteException();
	std::cout	<< b.getName()
				<< " executed "
				<< getName()
				<< std::endl;
	executeAction();
}

		//-------> Self Exceptions <-------//

const char*	AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char*	AForm::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

const char*	AForm::GradeTooLowForExecuteException::what() const throw()
{
	return ("Grade is too low for execute this form");
}

const char*	AForm::formNotSignedException::what() const throw()
{
	return ("Form not signed");
}

		//-------> Other <-------//

std::ostream&	operator<<(std::ostream& os, const AForm& f)
{
	os	<< "AForm name : "	<< f.getName()		<< std::endl
		<< "Signed : "		<< f.getSigned()	<< std::endl
		<< "SignGrade : "	<< f.getSignGrade()	<< std::endl
		<< "ExecGrade : "	<< f.getExecGrade();
	return (os);
}