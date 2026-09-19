# include "../includes/Weapon.hpp"

Weapon::Weapon( std::string Type )
{
	_type = Type;
}

const std::string&	Weapon::getType() const
{
	return (_type);
}

void			Weapon::setType( std::string Type )
{
	_type = Type;
}

Weapon::~Weapon()
{
	std::cout << _type << " is destroy!" << std::endl;
}