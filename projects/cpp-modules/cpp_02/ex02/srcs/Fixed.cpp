# include "../includes/Fixed.hpp"

/*
class	Fixed
{
	private:
		int					_value;
		static const int	_bits = 8;
	public:
		Fixed();
		Fixed( const Fixed& copy );
		Fixed( const float fValue );
		Fixed( const int iValue );
		float					toFloat( void ) const;
		int						toInt( void ) const;
		static Fixed&			min( Fixed& f1, Fixed& f2 );
		static const Fixed&		min( const Fixed& f1, const Fixed& f2 );
		static Fixed&			max( Fixed& f1, Fixed& f2 );
		static const Fixed&		max( const Fixed& f1, const Fixed& f2 );
		~Fixed();
		Fixed&					operator=( const Fixed& other );

		bool					operator>( const Fixed& other ) const;
		bool					operator<( const Fixed& other ) const;
		bool					operator>=( const Fixed& other ) const;
		bool					operator<=( const Fixed& other ) const;
		bool					operator==( const Fixed& other ) const;
		bool					operator!=( const Fixed& other ) const;

		Fixed					operator+( const Fixed& other ) const;
		Fixed					operator-( const Fixed& other ) const;
		Fixed					operator*( const Fixed& other ) const;
		Fixed					operator/( const Fixed& other ) const;

		Fixed&					operator++();
		Fixed					operator++( int );
		Fixed&					operator--();
		Fixed					operator--( int );

		friend std::ostream&	operator<<( std::ostream& out, const Fixed& fixed );
};
*/

const int	Fixed::_bits = 8;

//				constructeur / destructeur				//

Fixed::Fixed( void )
{
	_value = 0;
}

Fixed::Fixed( const Fixed& copy )
{
	*this = copy;
}

Fixed::Fixed( const float fValue )
{
	_value = roundf(fValue * (1 << _bits));
}

Fixed::Fixed( const int iValue )
{
	_value = iValue << _bits;
}

Fixed::~Fixed( void )
{}

//				function				//

float	Fixed::toFloat( void ) const
{
	return ((float)_value / (1 << _bits));
}

int		Fixed::toInt( void ) const
{
	return (_value >> _bits);
}

Fixed&			Fixed::min( Fixed& f1, Fixed& f2 )
{
	return ( (f1 < f2) ? f1 : f2 );
}

const Fixed&		Fixed::min( const Fixed& f1, const Fixed& f2 )
{
	return ( (f1 < f2) ? f1 : f2 );
}

Fixed&			Fixed::max( Fixed& f1, Fixed& f2 )
{
	return ( (f1 > f2) ? f1 : f2 );
}

const Fixed&		Fixed::max( const Fixed& f1, const Fixed& f2 )
{
	return ( (f1 > f2) ? f1 : f2 );
}

//				operateurs				//

Fixed&	Fixed::operator=( const Fixed& other )
{
	if (this != &other)
		_value = other._value;
	return( *this );
}

bool					Fixed::operator>( const Fixed& other ) const
{
	return ( _value > other._value );
}

bool					Fixed::operator<( const Fixed& other ) const
{
	return ( _value < other._value );
}

bool					Fixed::operator>=( const Fixed& other ) const
{
	return ( _value >= other._value );
}

bool					Fixed::operator<=( const Fixed& other ) const
{
	return ( _value <= other._value );
}

bool					Fixed::operator==( const Fixed& other ) const
{
	return ( _value == other._value );
}

bool					Fixed::operator!=( const Fixed& other ) const
{
	return ( _value != other._value );
}

Fixed					Fixed::operator+( const Fixed& other ) const
{
	return ( Fixed(this->toFloat() + other.toFloat()) );
}

Fixed					Fixed::operator-( const Fixed& other ) const
{
	return ( Fixed(this->toFloat() - other.toFloat()) );
}

Fixed					Fixed::operator*( const Fixed& other ) const
{
	return ( Fixed(this->toFloat() * other.toFloat()) );
}

Fixed					Fixed::operator/( const Fixed& other ) const
{
	if (other._value == 0)
	{
		std::cout << "Error: Divition by zero" << std::endl;
		return ( Fixed(0) );
	}
	return ( Fixed(this->toFloat() / other.toFloat()) );
}

Fixed&					Fixed::operator++()
{
	_value++;
	return ( *this );
}

Fixed					Fixed::operator++( int )
{
	Fixed	tmp( *this );
	_value++;
	return ( tmp );
}

Fixed&					Fixed::operator--()
{
	_value--;
	return ( *this );
}

Fixed					Fixed::operator--( int )
{
	Fixed	tmp( *this );
	_value--;
	return ( *this );
}

std::ostream&	operator<<( std::ostream& out, const Fixed& fixed )
{
	out << fixed.toFloat();
	return (out);
}