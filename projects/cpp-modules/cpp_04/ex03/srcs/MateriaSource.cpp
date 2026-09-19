//-------> ./srcs.MateriaSource.cpp <-------//

#include "../includes/MateriaSource.hpp"

/*
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
*/

MateriaSource::MateriaSource()
{
	std::cout	<< "MateriaSource constructor" << std::endl;

	for ( int i = 0; i < 4; i++ )
		_templates[i] = NULL;
}

MateriaSource::MateriaSource( const MateriaSource& other )
{
	std::cout	<< "MateriaSource constructor copy" << std::endl;

	for ( int i = 0; i < 4; i++ )
	{
		if ( other._templates[i] )
			_templates[i] = other._templates[i]->clone();
		else
			_templates[i] = NULL;
	}
}

MateriaSource::~MateriaSource()
{
	std::cout	<< "MateriaSource destructor" << std::endl;

	for ( int i = 0; i < 4; i++ )
	{
		if ( _templates[i] )
			delete _templates[i];
	}
}

MateriaSource&	MateriaSource::operator=( const MateriaSource& other )
{
	std::cout	<< "AMateria copy assignment operator called"
				<< std::endl;

	if ( this != &other )
	{
		for ( int i = 0; i < 4; i++ )
		{
			if ( _templates[i] )
			{
				delete _templates[i];
				_templates[i] = NULL;
			}
			if ( other._templates[i] )
				_templates[i] = other._templates[i]->clone();
		}
	}
	return ( *this );
}

//-------> IMateriaSource interface <-------//

void		MateriaSource::learnMateria( AMateria* m )
{
	if ( !m )
	{
		std::cout	<< "Can't learn NULL materia" << std::endl;
		return ;
	}

	for ( int i = 0; i < 4; i++ )
	{
		if ( !_templates[i] )
		{
			_templates[i] = m;
			std::cout	<< "New template learn" << std::endl;
			return ;
		}
	}
	std::cout	<< "No space for learn a new template" << std::endl;
}

AMateria*	MateriaSource::createMateria( const std::string& type )
{
	for ( int i = 0; i< 4; i++ )
	{
		if ( _templates[i] && _templates[i]->getType() == type)
		{

			return ( _templates[i]->clone() );
		}
	}
	std::cout	<< "Unknown materia type: " << type << std::endl;

	return ( NULL );
}
