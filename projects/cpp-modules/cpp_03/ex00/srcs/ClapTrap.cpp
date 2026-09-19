# include "../includes/ClapTrap.hpp"

/*
class ClapTrap
{
	private:
		std::string		_name;
		unsigned int	_HP;
		unsigned int	_EP;
		unsigned int	_attackDamage;
	public:
		ClapTrap();
		ClapTrap( std::string name );
		~ClapTrap();
		void	attack( const std::string& target );
		void	takeDamage( unsigned int amount );
		void	beRepaired( unsigned int amount );
};
*/

ClapTrap::ClapTrap() : _name( "unname" ), _HP( 10 ), _EP( 10 ), _attackDamage( 0 )
{
	std::cout << "Base ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap( std::string name ) : _name( name ), _HP( 10 ), _EP( 10 ), _attackDamage( 0 )
{
	std::cout << "ClapTrap constructor called and named: " << _name << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Claptrap " << _name << " destructor called" << std::endl;
}

void	ClapTrap::attack( const std::string& target )
{
	if ( _EP <= 0 )
	{
		std::cout << "ClapTrap " << _name << " hase no EP left." << std::endl;
		return ;
	}
	else if ( _HP <= 0 )
	{
		std::cout << "ClapTrap " << _name << " hase no HP left." << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
	_EP--;
}

void	ClapTrap::takeDamage( unsigned int amount )
{
	std::cout << "ClapTrap " << _name << " take " << amount << " points of damage!" << std::endl;
	_HP -= amount;
	if ( _HP < 0 )
		_HP = 0;
}

void	ClapTrap::beRepaired( unsigned int amount )
{
	if ( _EP == 0 )
		std::cout << "ClapTrap hase no EP left." << std::endl;
	if ( _HP == 10 )
	{
		std::cout << "ClapTrap " << _name << " is already at max HP!" << std::endl;
		return ;
	}
	_HP = ( _HP + amount > 10 ) ? 10 : _HP + amount;
	_EP--;
	std::cout << "ClapTrap " << _name << " self repaire " << amount << " to his HP!" << std::endl;
}