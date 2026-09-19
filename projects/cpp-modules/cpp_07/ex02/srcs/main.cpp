//-------> ./srcs/Main.cpp <-------//

#include <iostream>
#include <string>
#include "../includes/Array.hpp"

struct Point
{
	int x;
	int y;

	Point(int a = 0, int b = 0) : x(a), y(b) {}
};

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return (os);
}

int main()
{
	std::cout << "=== Array<int> ===" << std::endl;
	Array<int> a(5);

	for (unsigned int i = 0; i < a.size(); ++i)
		a[i] = i * 10;
	for (unsigned int i = 0; i < a.size(); ++i)
		std::cout << "a[" << i << "] = " << a[i] << std::endl;

	std::cout << "\n=== Array<std::string> ===" << std::endl;
	Array<std::string> b(3);

	b[0] = "hello";
	b[1] = "world";
	b[2] = "template";
	for (unsigned int i = 0; i < b.size(); ++i)
		std::cout << "b[" << i << "] = " << b[i] << std::endl;

	std::cout << "\n=== Array<Point> ===" << std::endl;
	Array<Point> c(2);

	c[0] = Point(1, 2);
	c[1] = Point(3, 4);
	for (unsigned int i = 0; i < c.size(); ++i)
		std::cout << "c[" << i << "] = " << c[i] << std::endl;

	// Test des exceptions
	try {
		std::cout << "\nAccès hors limite : " << a[10] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception attrapée : " << e.what() << std::endl;
	}

	return (0);
}
