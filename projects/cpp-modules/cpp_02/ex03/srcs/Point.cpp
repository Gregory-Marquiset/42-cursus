# include "../includes/Point.hpp"

Point::Point() : _x(0), _y(0)
{}

Point::Point( const float X, const float Y ) : _x(X), _y(Y)
{}

Point::Point( const Point& copy ) : _x(copy._x), _y(copy._y)
{}

Point::~Point()
{}

Fixed	Point::getX() const
{
	return( _x );
}

Fixed	Point::getY() const
{
	return( _y );
}

Point&	Point::operator=( const Point& other )
{
	(void)other;
	return( *this );
}
