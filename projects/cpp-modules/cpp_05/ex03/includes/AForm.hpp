//-------> ./includes/AForm.hpp <-------//

# ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
class Bureaucrat;

class	AForm
{
	private :
		std::string	_name;
		bool		_signed;
		int			_signGrade;
		int			_execGrade;
	public :
		AForm();
		AForm(const AForm& copy);
		AForm&	operator=(const AForm& other);
		virtual	~AForm();
		AForm(std::string name, int signGrade, int execGrade);

		//-------> Self methode <-------//
		const std::string	getName() const;
		bool				getSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;

		void				setName(std::string name);
		void				setSigned(bool b);
		void				setSignGrade(int signGrade);
		void				setExecGrade(int execGrade);

		void				beSign(const Bureaucrat& b);
		void				execute(const Bureaucrat& b) const;
		virtual void		executeAction() const = 0;


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
		class	GradeTooLowForExecuteException : public std::exception
		{
			public :
				const char*	what() const throw();
		};
		class	formNotSignedException : public std::exception
		{
			public :
				const char*	what() const throw();
		};
};

		//-------> Other <-------//
std::ostream&	operator<<(std::ostream& os, const AForm& f);

#endif	//	AFORM_HPP