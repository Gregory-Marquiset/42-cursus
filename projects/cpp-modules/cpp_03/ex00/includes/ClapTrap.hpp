# ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

# include <iostream>

/*
It will be called ClapTrap and will have the following private attributes initialized
to the values specified in brackets:
• Name, which is passed as parameter to a constructor
• Hit points (10), represent the health of the ClapTrap
• Energy points (10)
• Attack damage (0)
Add the following public member functions so the ClapTrap looks more realistic:
• void attack(const std::string& target);
• void takeDamage(unsigned int amount);
• void beRepaired(unsigned int amount);
*/

class ClapTrap
{
	private:
		std::string	_name;
		int			_HP;
		int			_EP;
		int			_attackDamage;
	public:
		ClapTrap();
		ClapTrap( std::string name );
		~ClapTrap();

		void	attack( const std::string& target );
		void	takeDamage( unsigned int amount );
		void	beRepaired( unsigned int amount );
};

#endif	//CLAPTRAP_HPP