# include <../includes/Zombie.hpp>

Zombie::Zombie()
{
	_name = "unnamed";
	_index = 0;
}

void	Zombie::announce() const
{
	std::cout << _index + 1 << " " << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setParams( std::string name ,int N )
{
	if ( name[0] )
		_name = name;
	_index = N;
}

Zombie::~Zombie()
{
	std::cout << _index + 1 << " " << _name << " is now dead?" << std::endl;
}