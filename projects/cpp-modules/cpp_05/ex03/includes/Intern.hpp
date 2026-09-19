//-------> ./includes/Intern.hpp <-------//

# ifndef INTERN_HPP
#define INTERN_HPP

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

		//-------> FormTable struct <-------//

struct	FormTable
{
	const std::string	name;
	AForm* (*create)(const std::string&);
};

		//-------> Intern class <-------//

class	Intern
{
	private :
		static const FormTable	_formTable[3];
	public :
		Intern();
		Intern(const Intern& copy);
		Intern&	operator=(const Intern& other);
		~Intern();

		//-------> Self methode <-------//
		AForm*	makeForm(std::string form, std::string target);

		//-------> Self Exceptions <-------//
		class	unknownFormException : public std::exception
		{
			public :
				const char*	what() const throw();
		};
};

#endif //	INTERN_HPP