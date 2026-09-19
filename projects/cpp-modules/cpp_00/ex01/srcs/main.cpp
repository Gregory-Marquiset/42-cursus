# include "../includes/PhoneBook.hpp"

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;

	while (true)
	{
		std::cout << "Enter command: ";
		if (!std::getline(std::cin, command))
			break ;
		if (command == "EXIT")
			break ;
		else if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else
			std::cout << "Command invalide." << std::endl;
	}
	return (0);
}