#ifndef	ZOMBIE_HPP
#define	ZOMBIE_HPP

# include <string>
# include <iostream>
# include <cstdlib>

class	Zombie
{
	private:
		std::string	_name;
		int			_index;
	public:
		Zombie();
		void	announce() const;
		void	setParams( std::string name ,int N );
		~Zombie();
};

Zombie*	zombieHorde( int N, std::string name );

#endif //ZOMBIE_HPP