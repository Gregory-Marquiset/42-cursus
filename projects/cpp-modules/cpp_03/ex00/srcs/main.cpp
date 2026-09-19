# include "../includes/ClapTrap.hpp"

int	main( void )
{
	ClapTrap	test("CL4P-TP");

	test.attack("CL4P-TP22");
	test.takeDamage(10);
	test.attack("CL4P-TP22");
	test.beRepaired(5);
	test.beRepaired(5);
	test.attack("CL4P-TP22");
	return (0);
}