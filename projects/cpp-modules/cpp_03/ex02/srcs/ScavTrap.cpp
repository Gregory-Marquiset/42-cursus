# include "../includes/ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	_HP = 100;
	_EP = 50;
	_attackDamage = 20;
    std::cout << "ScavTrap " << _name << " is created!" << std::endl;
}

ScavTrap::ScavTrap( std::string name ) : ClapTrap( name )
{
	_HP = 100;
	_EP = 50;
	_attackDamage = 20;
    std::cout << "ScavTrap " << _name << " is created!" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << _name << " is destroyed!" << std::endl;
}

void	ScavTrap::attack( const std::string& target )
{
	if (_EP > 0 && _HP > 0)
	{
		std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
		_EP--;
	}
	else
		std::cout << "ScavTrap hase no EP left." << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << _name << " is now in Gatekeeper mode!" << std::endl;
}