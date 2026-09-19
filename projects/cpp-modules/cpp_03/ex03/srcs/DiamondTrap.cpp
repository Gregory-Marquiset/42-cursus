# include "../includes/DiamondTrap.hpp"

DiamondTrap::DiamondTrap() :
	ClapTrap(), ScavTrap(), FragTrap()
{
	_HP = 100;
	_EP = 100;
	_attackDamage = 30;
    std::cout << "DiamondTrap " << _name << " is created!" << std::endl;
}

DiamondTrap::DiamondTrap( std::string name ) :
	ClapTrap( name + "_clap" ), ScavTrap( name ), FragTrap( name ), _name( name )
{
	_HP = FragTrap::_HP;
	_EP = ScavTrap::_EP;
	_attackDamage = FragTrap::_attackDamage;
    std::cout << "DiamondTrap " << _name << " is created!" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << _name << " is destroyed!" << std::endl;
}

void	DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap name: " << _name 
				<< ", ClapTrap name: " << ClapTrap::_name << std::endl;
}