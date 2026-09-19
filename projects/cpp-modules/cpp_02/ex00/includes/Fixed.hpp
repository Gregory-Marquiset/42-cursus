# ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>

class	Fixed
{
	private:
		int					_value;
		static const int	_bits;
	public:
		Fixed();
		Fixed( const Fixed& copy );
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		~Fixed();
		Fixed&	operator=( const Fixed& other );
};

#endif	//FIXED_HPP