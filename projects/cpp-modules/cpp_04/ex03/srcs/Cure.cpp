//-------> ./srcs.Cure.cpp <-------//

#include "../includes/Cure.hpp"

/*
class	Cure : public AMateria
{
	public:
		Cure();
		Cure( const Cure& other );
		Cure ( const std::string& type );
		~Cure();
		Cure&	operator=( const Cure& other );

		//-------> AMateria methode <-------//
		AMateria*	clone( void ) const;
		void		use( ICharacter& target );
};
*/

Cure::Cure() : AMateria::AMateria( "cure" )
{
	std::cout	<< _type << " constructor" << std::endl;
}

Cure::Cure( const Cure& other ) : AMateria::AMateria( other )
{
	std::cout	<< _type << " constructor copy" << std::endl;
}

Cure::Cure( const std::string& type ) : AMateria::AMateria( type )
{
	std::cout	<< _type << " constructor type" << std::endl;
}

Cure::~Cure()
{
	std::cout	<< _type << " destructor" << std::endl;
}

Cure&	Cure::operator=( const Cure& other )
{
	std::cout	<< "Cure copy assignment operator called"
				<< std::endl;

	if ( this != &other )
		_type = other.getType();

	return ( *this );
}

//-------> AMateria methode <-------//

AMateria*	Cure::clone( void ) const
{
	return ( new Cure( *this ) );
}

void		Cure::use( ICharacter& target )
{
	std::cout	<< "* Call a cure on " << target.getName()
				<< " *" << std::endl;
}
