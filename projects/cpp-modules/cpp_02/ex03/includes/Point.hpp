# ifndef POINT_HPP
#define POINT_HPP

# include <iostream>
# include <cmath>
# include "Fixed.hpp"

class Point
{
	private:
		const Fixed	_x;
		const Fixed	_y;
	public:
		Point();
		Point( const float X, const float Y );
		Point( const Point& copy );
		~Point();
		Fixed	getX() const;
		Fixed	getY() const;
		Point&	operator=( const Point& other );
};

bool	bsp( Point const a, Point const b, Point const c, Point const point);

#endif	//POINT_HPP