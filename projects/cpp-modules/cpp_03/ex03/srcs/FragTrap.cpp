# include "../includes/FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	_HP = 100;
	_EP = 100;
	_attackDamage = 30;
    std::cout << "FragTrap " << _name << " is created!" << std::endl;
}

FragTrap::FragTrap( std::string name ) : ClapTrap( name )
{
	_HP = 100;
	_EP = 100;
	_attackDamage = 30;
    std::cout << "FragTrap " << _name << " is created!" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << _name << " is destroyed!" << std::endl;
}

void	FragTrap::attack( const std::string& target )
{
	if (_EP > 0 && _HP > 0)
	{
		std::cout << "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
		_EP--;
	}
	else
		std::cout << "FragTrap hase no EP left." << std::endl;
}

void	FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << _name << " do a high fives!" << std::endl;
}