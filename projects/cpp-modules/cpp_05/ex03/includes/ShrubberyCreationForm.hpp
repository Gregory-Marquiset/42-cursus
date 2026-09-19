//-------> ./includes/ShrubberyCreationForm.hpp <-------//

// ShrubberyCreationForm: Required grades: sign 145, exec 137
// Creates a file <target>_shrubbery in the working directory and writes ASCII trees
// inside it.

# ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class	SCForm : public AForm
{
	private :
		std::string	_target;
	public :
		SCForm();
		SCForm(const SCForm& copy);
		SCForm&				operator=(const SCForm& other);
		~SCForm();
		SCForm(const std::string target);

		//-------> Self methode <-------//
		const std::string	getTarget() const;

		void				setTarget(const std::string target);
		//-------> AForm methode <-------//
		void				executeAction() const;
};

#endif //	SHRUBBERYCREATIONFORM_HPP