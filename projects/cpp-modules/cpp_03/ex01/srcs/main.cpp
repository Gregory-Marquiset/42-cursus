# include "../includes/ClapTrap.hpp"
# include "../includes/ScavTrap.hpp"

int	main( void )
{
	ClapTrap	clap("CL4P-TP");
	ScavTrap	scav("SC4V-TP");

	clap.attack("CL4P-TP22");
	scav.attack("SC4V-TP44");
	scav.guardGate();
	
	return (0);
}