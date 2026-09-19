//-------> ./includes/Bureaucrat.hpp <-------//

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "Form.hpp"

class	Bureaucrat
{
	private:
		std::string		_name;
		int				_grade;
	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat&	operator=(const Bureaucrat& other);
		~Bureaucrat();
		Bureaucrat(std::string name, int grade);

		//-------> Self methode <-------//
		const std::string	getName() const;
		int					getGrade() const;
		void				incrementGrade();
		void				decrementGrade();
		void				signForm( Form& f);

		//-------> Self Exceptions <-------//
		class	GradeTooHighException : public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class	GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

		//-------> Other <-------//
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& b);

# endif	//	BUREAUCRAT_HPP