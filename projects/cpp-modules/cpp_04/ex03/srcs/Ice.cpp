//-------> ./srcs.Ice.cpp <-------//

#include "../includes/Ice.hpp"

/*
class	Ice : public AMateria
{
	public:
		Ice();
		Ice( const Ice& other );
		Ice( const std::string& type );
		~Ice();
		Ice&	operator=( const Ice& other );

		//-------> AMateria methode <-------//
		AMateria*	clone() const;
		void		use( ICharacter& target );
};
*/

Ice::Ice() : AMateria::AMateria( "ice" )
{
	std::cout	<< _type << " constructor" << std::endl;
}

Ice::Ice( const Ice& other ) : AMateria::AMateria( other )
{
	std::cout	<< _type << " constructor copy" << std::endl;
}

Ice::Ice( const std::string& type ) : AMateria::AMateria( type )
{
	std::cout	<< _type << " constructor type" << std::endl;
}

Ice::~Ice()
{
	std::cout	<< _type << " destructor" << std::endl;
}

Ice&	Ice::operator=( const Ice& other )
{
	std::cout	<< "Ice copy assignement called"
				<< std::endl;

	if ( this != &other )
		_type = other.getType();

	return ( *this );
}

//-------> AMateria methode <-------//

AMateria*	Ice::clone( void ) const
{
	return ( new Ice( *this ) );
}

void		Ice::use( ICharacter& target )
{
    std::cout	<< "* shoots an ice bolt at " << target.getName()
				<< " *" << std::endl;
}
