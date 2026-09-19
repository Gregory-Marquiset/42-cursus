# include "../includes/Point.hpp"

int	main( void )
{
	Point a(0, 0);
	Point b(0, 10);
	Point c(5, 5);

	Point p1(2, 5);
	Point p2(0, 0);
	Point p3(0, 10);
	Point p4(5, 5);
	Point p5(50, 50);
	Point p7(4, 5);

	std::cout << "Is p1 inside? " << (bsp(a, b, c, p1) ? "Yes" : "No") << std::endl;
	std::cout << "Is p2 inside? " << (bsp(a, b, c, p2) ? "Yes" : "No") << std::endl;
	std::cout << "Is p3 inside? " << (bsp(a, b, c, p3) ? "Yes" : "No") << std::endl;
	std::cout << "Is p4 inside? " << (bsp(a, b, c, p4) ? "Yes" : "No") << std::endl;
	std::cout << "Is p5 inside? " << (bsp(a, b, c, p5) ? "Yes" : "No") << std::endl;
	std::cout << "Is p6 inside? " << (bsp(a, b, c, p7) ? "Yes" : "No") << std::endl;

	return (0);
}