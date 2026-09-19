# ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

# include <ScavTrap.hpp>
# include <iostream>

class FragTrap : public ClapTrap
{
	public:
		FragTrap();
		FragTrap( std::string name );
		~FragTrap();

		void	attack( const std::string& target );
		void	highFivesGuys();
};

#endif	//FRAGTRAP_HPP