//-------> ./includes/PresidentialPardonForm.hpp <-------//

# ifndef PRESIDENTIALPARDON_HPP
#define PRESIDENTIALPARDON_HPP

#include "AForm.hpp"

class	PPForm : public AForm
{
	private :
		std::string	_target;
	public :
		PPForm();
		PPForm(const PPForm& copy);
		~PPForm();
		PPForm&			operator=(const PPForm& other);
		PPForm(const std::string target);

		//-------> Self methode <-------//
		const std::string	getTarget() const;

		void				setTarget(const std::string target);

		//-------> AForm methode <-------//
		void				executeAction() const;
};

#endif //	PRESIDENTIALPARDON_HPP