#include "../includes/Harl.hpp"

/*
"DEBUG" level: Debug messages contain contextual information. They are mostly
used for problem diagnosis.
Example: "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!"

• "INFO" level: These messages contain extensive information. They are helpful for
tracing program execution in a production environment.
Example: "I cannot believe adding extra bacon costs more money. You didn’t put
enough bacon in my burger! If you did, I wouldn’t be asking for more!"

• "WARNING" level: Warning messages indicate a potential issue in the system.
However, it can be handled or ignored.
Example: "I think I deserve to have some extra bacon for free. I’ve been coming for
years whereas you started working here since last month."

• "ERROR" level: These messages indicate an unrecoverable error has occurred.
This is usually a critical issue that requires manual intervention.
Example: "This is unacceptable! I want to speak to the manager now."
*/

// class	Harl
// {
// 	private:
// 		void	debug( void );
// 		void	info( void );
// 		void	warning( void );
// 		void	error( void );
// 	public:
// 		void	complain( std::string level );
// };

void	Harl::debug( void )
{
	std::cout << "[ DEBUG ]\nI love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void	Harl::info( void )
{
	std::cout << "[ INFO ]\nI cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void	Harl::warning( void )
{
	std::cout << "[ WARNING ]\nI think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void	Harl::error( void )
{
	std::cout << "[ ERROR ]\nThis is unacceptable! I want to speak to the manager now." << std::endl;
}

void	Harl::complain( std::string level )
{
	std::string	log[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void	(Harl::*function[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	int	i = 0;
	for (i = 0; i < 4; i++)
	{
		if (level == log[i])
			break ;
	}
	switch (i)
	{
        case 0: (this->*function[0])(), std::cout << std::endl;
        case 1: (this->*function[1])(), std::cout << std::endl;
        case 2: (this->*function[2])(), std::cout << std::endl;
        case 3: (this->*function[3])(); break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
}