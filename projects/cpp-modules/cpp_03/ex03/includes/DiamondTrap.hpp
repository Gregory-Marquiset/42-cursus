# ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

# include <FragTrap.hpp>
# include <iostream>

class DiamondTrap : public ScavTrap, public FragTrap
{
	private:
		std::string	_name;
	public:
		DiamondTrap();
		DiamondTrap( std::string name );
		~DiamondTrap();

		void	whoAmI();
		using ScavTrap::attack;
};

#endif	//DIAMONDTRAP_HPP