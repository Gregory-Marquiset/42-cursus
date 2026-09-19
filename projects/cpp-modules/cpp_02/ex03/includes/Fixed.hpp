# ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <cmath>

class	Fixed
{
	private:
		int					_value;
		static const int	_bits;
	public:
		Fixed();
		Fixed( const Fixed& copy );
		Fixed( const float fValue );
		Fixed( const int iValue );
		~Fixed();

		float					toFloat( void ) const;
		int						toInt( void ) const;
		static Fixed&			min( Fixed& f1, Fixed& f2 );
		static const Fixed&		min( const Fixed& f1, const Fixed& f2 );
		static Fixed&			max( Fixed& f1, Fixed& f2 );
		static const Fixed&		max( const Fixed& f1, const Fixed& f2 );

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

#endif	//FIXED_HPP