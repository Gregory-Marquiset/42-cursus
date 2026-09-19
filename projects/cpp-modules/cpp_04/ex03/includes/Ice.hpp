//-------> ./includes.Ice.hpp <-------//

# ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class	Ice : public AMateria
{
	public:
		Ice();
		Ice( const Ice& other );
		Ice( const std::string& type );
		~Ice();
		Ice&	operator=( const Ice& other );

		//-------> AMateria methode <-------//
		AMateria*	clone( void ) const;
		void		use( ICharacter& target );
};

#endif // ICE_HPP