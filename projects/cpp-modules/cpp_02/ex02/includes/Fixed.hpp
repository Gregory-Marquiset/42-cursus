# ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <cmath>

/*
Ajoutez à votre classe des fonctions membres publiques afin de surcharger les opérateurs suivants :
	• Les 6 opérateur de comparaison : >, <, >=, <=, == et !=.
	• Les 4 opérateurs d'arithmétiques : +, -, *, et /.
	• Les 4 opérateurs d’incrémentation et de décrémentation (pré-incrémentation et
		post-incrémentation, pré-décrémentation et post-décrémentation) qui diminueront
		la valeur du nombre à virgule fixe d’unité ϵ tel que 1 + ϵ > 1.

Ajoutez à votre classe ces quatre fonctions membres publiques surchargées :
	• Une fonction membre statique min prenant en paramètres deux références sur des
		nombres à virgule fixe et qui retourne le plus petit d’entre eux.
	• Une fonction membre statique min prenant en paramètres deux références sur des
		nombres à virgule fixe constants et qui retourne le plus petit d’entre eux.
	• Une fonction membre statique max prenant en paramètres deux références sur des
		nombres à virgule fixe et qui retourne le plus grand d’entre eux.
	• Une fonction membre statique max prenant en paramètres deux références sur des
		nombres à virgule fixe constants et qui retourne le plus grand d’entre eux.
*/

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