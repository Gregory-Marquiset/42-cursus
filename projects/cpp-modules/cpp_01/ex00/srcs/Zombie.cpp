# include "../includes/Zombie.hpp"

Zombie::Zombie(std::string initName)
{
	_name = initName;
}

Zombie::~Zombie( void )
{
	std::cout << _name << " destroyed." << std::endl;
}

void    Zombie::announce( void ) const
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}