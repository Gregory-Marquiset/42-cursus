# ifndef HARL_HPP
#define HARL_HPP

# include <iostream>
#include <string>

/*
You are going to automate Harl. It won’t be difficult since it always says the same
things. You have to create a Harl class with the following private member functions:
• void debug( void );
• void info( void );
• void warning( void );
• void error( void );

Harl also has a public member function that calls the four member functions above
depending on the level passed as parameter:
void complain( std::string level );

The goal of this exercise is to use pointers to member functions. This is not a
suggestion. Harl has to complain without using a forest of if/else if/else. It doesn’t think
twice!
Create and turn in tests to show that Harl complains a lot. You can use the examp
*/

class	Harl
{
	private:
		void	debug( void );
		void	info( void );
		void	warning( void );
		void	error( void );
	public:
		void	complain( std::string level );
};

#endif	//HARL_HPP