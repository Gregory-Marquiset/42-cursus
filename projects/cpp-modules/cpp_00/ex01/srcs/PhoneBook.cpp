# include "../includes/PhoneBook.hpp"

PhoneBook::PhoneBook() : index(0) {}

void	PhoneBook::addContact()
{
	contacts[index].getInfo();
	index++;
	if (index == 8)
		index = 0;
}

static bool st_isValidInteger(const std::string& str, int& result) 
{
	std::stringstream ss(str);
	ss >> result;

	return !ss.fail() && ss.eof();
}

void	PhoneBook::searchContact()
{
	std::string	input;
	int			index;

	std::cout << "     Index|First name| Last name|  Nickname|" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	for (int i = 0; i < 8; i++)
		contacts[i].displaySummary(i + 1);
	while (true)
	{
		std::cout << "Enter the index of the contact to view details (1-8): ";

		std::getline(std::cin, input);
		if (std::cin.eof())
		{
			std::cout << "\nInput interrupted. Exiting search." << std::endl;
			return ;
		}
		if (input.empty())
		{
			std::cout << "Input cannot be empty." << std::endl;
			continue ;
		}
		if (!st_isValidInteger(input, index))
		{
			std::cout << "Invalid input." << std::endl;
			continue ;
		}
		if (index >= 1 && index <= 8)
		{
			contacts[index - 1].displayDetails();
			break ;
		}
		else
			std::cout << "Invalid index." << std::endl;
	}
}