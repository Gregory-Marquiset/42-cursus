# include "../includes/Contact.hpp"

void	Contact::getInfo()
{
	std::cout << "First name: ";
	std::getline(std::cin, firstName);
	std::cout << "Last name: ";
	std::getline(std::cin, lastName);
	std::cout << "Nickname: ";
	std::getline(std::cin, nickName);
	std::cout << "Phone number: ";
	std::getline(std::cin, phoneNumber);
	std::cout << "Darkest secret: ";
	std::getline(std::cin, darkestSecret);
}

void	Contact::displaySummary(int index) const
{
	std::cout << std::setw(10) << index << "|"
	    << std::setw(10) << (firstName.length() > 10 ? firstName.substr(0, 9) + "." : firstName) << "|" 
		<< std::setw(10) << (lastName.length() > 10 ? lastName.substr(0, 9) + "." : lastName) << "|"
		<< std::setw(10) << (nickName.length() > 10 ? nickName.substr(0, 9) + "." : nickName) << "|"
		<< std::endl;
}

void	Contact::displayDetails() const
{
	std::cout << "First name: " << firstName << std::endl;
	std::cout << "Last name: " << lastName << std::endl;
	std::cout << "Nickname: " << nickName << std::endl;
	std::cout << "Phone number: " << phoneNumber << std::endl;
	std::cout << "Darkest secret: " << darkestSecret << std::endl;
}