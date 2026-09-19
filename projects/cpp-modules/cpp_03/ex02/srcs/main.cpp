# include "../includes/FragTrap.hpp"

int	main( void )
{
	ClapTrap	clap("CL4P-TP");
	ScavTrap	scav("SC4V-TP");
	FragTrap	frag("FR4G-TP");

	clap.attack("CL4P-TP22");
	scav.attack("SC4V-TP44");
	frag.attack("FR4G-TP66");
	scav.guardGate();
	frag.highFivesGuys();
	
	return (0);
}