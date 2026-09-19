# include "../includes/Fixed.hpp"

const int	Fixed::_bits = 8;

Fixed::Fixed( void )
{
	std::cout << "Default constructor called" << std::endl;
	_value = 0;
}

Fixed::Fixed( const Fixed& copy )
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::Fixed( const float fValue )
{
	std::cout << "Float constructor called" << std::endl;
	_value = roundf(fValue * (1 << _bits));
}

Fixed::Fixed( const int iValue )
{
	std::cout << "Int constructor called" << std::endl;
	_value = iValue << _bits;
}

int	Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

void	Fixed::setRawBits( int const raw )
{
	std::cout << raw << std::endl;
	_value = raw;
}


float	Fixed::toFloat( void ) const
{
	return ((float)_value / (1 << _bits));
}

int		Fixed::toInt( void ) const
{
	return (_value >> _bits);
}

Fixed::~Fixed( void )
{
	std::cout << "Destructor called" << std::endl;
}

Fixed&	Fixed::operator=( const Fixed& other )
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other._value;
	return( *this );
}

std::ostream&	operator<<( std::ostream& out, const Fixed& fixed )
{
	out << fixed.toFloat();
	return (out);
}