//-------> ./srcs/PresidentialPardonForm.cpp <-------//

# include "../includes/PresidentialPardonForm.hpp"
# include "../includes/Bureaucrat.hpp"

PPForm::PPForm() :
	AForm("PPForm 00", 25, 5), _target("nothing")
{}

PPForm::PPForm(const PPForm& copy) :
	AForm(copy)
{
	*this = copy;
}

PPForm::~PPForm()
{}

PPForm&	PPForm::operator=(const PPForm& other)
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

PPForm::PPForm(const std::string target) :
	AForm("PPForm 00", 25, 5), _target(target)
{}

		//-------> Self methode <-------//

const std::string	PPForm::getTarget() const
{
	return (_target);
}

void				PPForm::setTarget(const std::string target)
{
	_target = target;
}

		//-------> AForm methode <-------//

void		PPForm::executeAction() const
{
	std::cout	<< getTarget()
				<< " has been pardoned by Zaphod Beeblebrox."
				<< std::endl;
}