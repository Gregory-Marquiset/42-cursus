#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>

class	Zombie
{
	private:
		std::string	_name;
	public:
		Zombie( std::string initName );
		void	announce( void ) const;
		~Zombie();
};

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

#endif //ZOMBIE_HPP