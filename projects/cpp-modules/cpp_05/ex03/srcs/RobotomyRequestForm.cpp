//-------> ./srcs/RobotomyRequestForm.cpp <-------//

#include "../includes/RobotomyRequestForm.hpp"

RRForm::RRForm() :
	AForm("RRForm 00", 72, 45), _target("nothing")
{}

RRForm::RRForm(const RRForm& copy) :
	AForm(copy)
{
	*this = copy;
}

RRForm&	RRForm::operator=(const RRForm& other)
{
	if (this != &other)
	{
		setName(other.getName());
		setSigned(other.getSigned());
		setSignGrade(other.getSignGrade());
		setExecGrade(other.getExecGrade());
		setTarget(other.getTarget());
	}
	return (*this);
}

RRForm::~RRForm()
{}

RRForm::RRForm(const std::string target) :
	AForm("RRForm 00", 72, 45), _target(target)
{}

		//-------> Self methode <-------//

const std::string	RRForm::getTarget() const
{
	return (_target);
}

void				RRForm::setTarget(const std::string target)
{
	_target = target;
}

		//-------> AForm methode <-------//

void				RRForm::executeAction() const
{
	std::cout	<< "BzzzzzZZZZZZzzzzZZZzzz... 🤖🔧" << std::endl;
	if (rand() % 2)
	{
		std::cout	<< _target
					<< " has been robotomized successfully!"
					<< std::endl;
	}
	else
	{
		std::cout	<< "Robotomy failed on "
					<< _target
					<< "."
					<< std::endl;
	}
}