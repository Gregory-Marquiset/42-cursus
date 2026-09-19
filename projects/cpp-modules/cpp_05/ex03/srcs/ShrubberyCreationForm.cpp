//-------> ./srcs/ShrubberyCreationForm.cpp <-------//

#include "../includes/ShrubberyCreationForm.hpp"

SCForm::SCForm() :
	AForm("nothing", 145, 137), _target("nothing")
{}

SCForm::SCForm(const SCForm& copy) :
	AForm(copy)
{
	*this = copy;
}

SCForm&	SCForm::operator=(const SCForm& other)
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

SCForm::~SCForm()
{}

SCForm::SCForm(const std::string target) :
	AForm("nothing", 145, 137), _target(target)
{}

		//-------> Self methode <-------//

const std::string	SCForm::getTarget() const
{
	return (_target);
}

void				SCForm::setTarget(const std::string target)
{
	_target = target;
}

		//-------> AForm methode <-------//

void				SCForm::executeAction() const
{
	std::ofstream	outfile((_target + "_shrubbery").c_str());

	if (!outfile)
	{
		std::cerr	<< "Failed to open output file!"
					<< std::endl;
		return ;
	}

    outfile << "       _-_\n"
               "    /~~   ~~\\\n"
               " /~~         ~~\\\n"
               "{~             ~}\n"
               " \\~ _-     -_ ~/\n"
               "   ~  \\\\ //  ~\n"
               "_- -   | | _- _\n"
               "  _ -  | |   -_\n"
               "    _.// \\\\._\n";

	outfile.close();
}