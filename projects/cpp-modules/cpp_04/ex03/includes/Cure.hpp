//-------> ./includes.Cure.hpp <-------//

# ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

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

#endif // CURE_HPP