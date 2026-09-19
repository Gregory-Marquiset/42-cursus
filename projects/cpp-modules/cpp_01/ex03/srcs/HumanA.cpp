# include "../includes/HumanA.hpp"

HumanA::HumanA( std::string Name ,Weapon& Weapon )
: _name(Name) ,_weapon(Weapon)
{}

void	HumanA::attack() const
{
	std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}

HumanA::~HumanA()
{
	std::cout << _name << " leave the fight!" << std::endl;
}