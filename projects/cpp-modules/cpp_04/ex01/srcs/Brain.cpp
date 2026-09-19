//-------> ./srcs/Brain.cpp <-------//

# include "../includes/Brain.hpp"

/*
class	Brain
{
	private:
		std::string	ideas[100];
	public:
		Brain();
		Brain( const Brain& copy );
		~Brain();
		Brain&	operator=( const Brain& other );

		//-------> Self methode <-------//
		std::string	getIdea( int i ) const;
		void		setIdea( int i, std::string idea );
};
*/

Brain::Brain()
{
	std::cout	<< "Default constructor for Brain as been called"
				<< std::endl;
}

Brain::Brain( const Brain& copy )
{
	*this = copy;
	std::cout	<< "Copy constructor for Brain as been called"
				<< std::endl;
}

Brain::~Brain()
{
	std::cout	<< "Destructor for Brain as been called"
				<< std::endl;
}

Brain&	Brain::operator=( const Brain& other )
{
	std::cout	<< "Copy assignment operator called"
				<< std::endl;
	if ( this != &other )
	{
		for ( int i = 0; i < 100; i++ )
			setIdea( i, other.getIdea( i ) );
	}
	return( *this );
}

//-------> Self methode <-------//

std::string Brain::getIdea( int i ) const
{
	if ( i < 0 || i >= 100 )
		return ( "" );
	return ( ideas[i] );
}

void        Brain::setIdea( int i, std::string idea )
{
	if ( i < 0 || i >= 100 )
		return ;
	ideas[i] = idea;
	return ;
}
