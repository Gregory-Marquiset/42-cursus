//-------> ./includes.AMateria.hpp <-------//

# ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include "interface/IMateriaSource.hpp"
#include "interface/ICharacter.hpp"

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

		//-------> Self methode <-------//
		void				setType( const std::string& type );
		const std::string&	getType( void ) const;
		virtual AMateria*	clone( void ) const = 0;
		virtual void		use( ICharacter& target );
};

#endif // AMATERIA_HPP
