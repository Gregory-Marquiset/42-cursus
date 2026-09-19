//-------> ./includes/RobotomyRequestForm.hpp <-------//

# ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class	RRForm : public AForm
{
	private :
		std::string	_target;
	public :
		RRForm();
		RRForm(const RRForm& copy);
		RRForm&			operator=(const RRForm& other);
		~RRForm();
		RRForm(const std::string target);

		//-------> Self methode <-------//
		const std::string	getTarget() const;

		void				setTarget(const std::string target);

		//-------> AForm methode <-------//
		void				executeAction() const;
};

#endif //	ROBOTOMYREQUESTFORM_HPP