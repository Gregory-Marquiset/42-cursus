# ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <cmath>


/*
• Un constructeur prenant un entier constant en paramètre et qui convertit celui-ci en virgule fixe.
Le nombre de bits de la partie fractionnaire est initialisé à 8 comme dans l’exercice 00.

• Un constructeur prenant un flottant constant en paramètre et qui convertit
celui-ci en virgule fixe.
Le nombre de bits de la partie fractionnaire est initialisé à 8 comme dans l’exercice 00.

• Une fonction membre float toFloat( void ) const;
qui convertit la valeur en virgule fixe en nombre à virgule flottante.

• Une fonction membre int toInt( void ) const;
qui convertit la valeur en virgule fixe en nombre entier.

Ajoutez également la fonction suivante à vos fichiers de la classe Fixed :
• Une surcharge de l’opérateur d’insertion («) qui insère une représentation en virgule flottante
du nombre à virgule fixe dans le flux de sortie (objet output stream) passé en paramètre.
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
		int						getRawBits( void ) const;
		void					setRawBits( int const raw );
		float					toFloat( void ) const;
		int						toInt( void ) const;
		~Fixed();
		Fixed&					operator=( const Fixed& other );
		friend std::ostream&	operator<<( std::ostream& out, const Fixed& fixed );
};

#endif	//FIXED_HPP