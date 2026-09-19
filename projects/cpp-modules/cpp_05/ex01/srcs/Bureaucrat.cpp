//-------> ./srcs/Bureaucrat.cpp <-------//

# include "../includes/Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Mr Smith"), _grade(150)
{}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
{
	*this = copy;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		_name = other.getName();
		_grade = other.getGrade();
	}
	return (*this);
}

Bureaucrat::~Bureaucrat()
{}

Bureaucrat::Bureaucrat(std::string name, int grade) :
	_name(name), _grade(grade)
{
	if (grade < 1)
		throw GradeTooLowException();
	if (grade > 150)
		throw GradeTooHighException();
}

 		//-------> Self methode <-------//

const std::string	Bureaucrat::getName() const
{
	return (_name);
}

int					Bureaucrat::getGrade() const
{
	return (_grade);
}

void				Bureaucrat::incrementGrade()
{
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	_grade--;
}

void				Bureaucrat::decrementGrade()
{
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	_grade++;
}

void				Bureaucrat::signForm( Form& f)
{
	try
	{
		f.beSign(*this);
		std::cout	<< getName()	<< " signed "
					<< f.getName()	<< std::endl;
	}
	catch (std::exception& e)
	{
		std::cout	<< getName()	<< " couldn't sign "
					<< f.getName()	<< " because "
					<< e.what() 	<< std::endl;
	}
}

 		//-------> Self Exceptions <-------//

const char*	Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char*	Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

		//-------> Other <-------//

std::ostream&	operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade();
	return (os);
}
