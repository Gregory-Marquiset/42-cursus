//-------> ./srcs.AMateria.cpp <-------//

#include "../includes/AMateria.hpp"

/*
class	AMateria
{
	protected:
		std::string	_type;
	public:
		AMateria();
		AMateria( const AMateria& other );
		AMateria( const std::string& type );
		virtual ~AMateria();
		AMateria&	operator=( const AMateria& other );

		//-------> IMateriaSource interface <-------//
		void		learnMateria( AMateria* );
		AMateria*	createMateria( const std::string& type );

		//-------> AMateria methode <-------//
		void				setType( const std::string& type );
		const std::string&	getType( void ) const;
		virtual AMateria*	clone( void ) const = 0;
		virtual void		use( ICharacter& target );
};
*/

AMateria::AMateria() : _type( "Neutral" )
{
	std::cout	<< _type << " AMateria constructor" << std::endl;
}

AMateria::AMateria( const AMateria& other ) : _type( other.getType() )
{
	std::cout	<< _type << " AMateria constructor copy" << std::endl;
}

AMateria::AMateria( const std::string& type ) : _type( type )
{
	std::cout	<< _type << " AMateria constructor type" << std::endl;
}

AMateria::~AMateria()
{
	std::cout	<< _type << " AMateria destructor" << std::endl;
}

AMateria&	AMateria::operator=( const AMateria& other )
{
	std::cout	<< "AMateria copy assignment operator called"
				<< std::endl;

	if ( this != &other )
		_type = other.getType();

	return ( *this );
}

//-------> Self methode <-------//

void    AMateria::setType( const std::string& type )
{
	_type = type;
}

const std::string& AMateria::getType( void ) const 
{
	return ( _type );
}

void		AMateria::use( ICharacter& target )
{
    std::cout	<< "* Neutral force applied on " << target.getName()
				<< " *" << std::endl;
}
