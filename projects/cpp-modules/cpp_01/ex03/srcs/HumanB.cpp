# include "../includes/HumanB.hpp"

HumanB::HumanB( std::string Name )
: _name(Name), _weapon(NULL)
{}

void	HumanB::setWeapon( Weapon& Weapon )
{
	_weapon = &Weapon;
}

void	HumanB::attack() const
{
	if ( _weapon )
		std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
	else
		std::cout << _name << " as no weapon!" << std::endl;
}

HumanB::~HumanB()
{
	std::cout << _name << " leave the fight!" << std::endl;
}