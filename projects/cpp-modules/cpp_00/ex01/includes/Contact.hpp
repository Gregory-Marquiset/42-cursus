#ifndef CONTACT_HPP
#define CONTACT_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>

class Contact
{
	private:
		std::string	firstName;
		std::string	lastName;
		std::string	nickName;
		std::string	phoneNumber;
		std::string	darkestSecret;
	public:
		void	getInfo();
		void	displaySummary(int index) const;
		void	displayDetails() const;
};

#endif //CONTACT_HPP