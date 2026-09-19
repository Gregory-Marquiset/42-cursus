//-------> ./includes.MateriaSource.hpp <-------//

# ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "interface/IMateriaSource.hpp"
#include "AMateria.hpp"

class	MateriaSource : public IMateriaSource
{
	private:
		AMateria*	_templates[4];
	public:
		MateriaSource();
		MateriaSource( const MateriaSource& other );
		~MateriaSource();
		MateriaSource&	operator=( const MateriaSource& other );

		//-------> IMateriaSource interface <-------//
		void		learnMateria( AMateria* );
		AMateria*	createMateria( const std::string& type );
};


#endif // MATERIASOURCE_HPP
