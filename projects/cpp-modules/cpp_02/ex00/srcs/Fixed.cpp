#include "../includes/Fixed.hpp"

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

Fixed::~Fixed( void )
{
	std::cout << "Destructor called" << std::endl;
}

Fixed&	Fixed::operator=( const Fixed& other )
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other.getRawBits();
	return( *this );
}