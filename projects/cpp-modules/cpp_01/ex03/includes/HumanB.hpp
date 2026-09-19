# include "../includes/HumanA.hpp"

class	HumanB
{
	private:
		std::string	_name;
		Weapon*		_weapon;
	public:
		HumanB( std::string Name );
		void	setWeapon( Weapon& Weapon );
		void	attack() const;
		~HumanB();
};