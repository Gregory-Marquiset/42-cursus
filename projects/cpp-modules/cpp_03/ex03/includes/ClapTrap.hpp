# ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
	protected:
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