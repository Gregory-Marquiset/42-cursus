# include "../includes/Weapon.hpp"

class	HumanA
{
	private:
		std::string	_name;
		Weapon&		_weapon;
	public:
		HumanA( std::string Name, Weapon& Weapon );
		void	attack() const;
		~HumanA();
};