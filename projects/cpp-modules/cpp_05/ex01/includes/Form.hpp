//-------> ./includes/Form.hpp <-------//

# ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
class Bureaucrat;

class	Form
{
	private :
		std::string	_name;
		bool		_signed;
		int			_signGrade;
		int			_execGrade;
	public :
		Form();
		Form(const Form& copy);
		Form&	operator=(const Form& other);
		~Form();
		Form(std::string name, int signGrade, int execGrade);

		//-------> Self methode <-------//
		const std::string	getName() const;
		bool				getSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;
		void				beSign(const Bureaucrat& b);

		//-------> Self Exceptions <-------//
		class	GradeTooHighException : public std::exception
		{
			public :
				const char*	what()const throw();
		};
		class	GradeTooLowException : public std::exception
		{
			public :
				const char*	what() const throw();
		};
};

		//-------> Other <-------//
std::ostream&	operator<<(std::ostream& os, const Form& f);

#endif	//	FORM_HPP