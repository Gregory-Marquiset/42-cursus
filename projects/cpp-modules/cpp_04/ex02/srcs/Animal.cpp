//-------> ./includes/Animal.hpp <-------//

# include "../includes/Animal.hpp"

/*
class Animal
{
	protected:
		std::string	_type;
	public:
		Animal();
		Animal( const Animal& copy );
		virtual	~Animal();
		Animal&	operator=( const Animal& other );

		std::string		getType() const;
		virtual void	makeSound() const = 0;
};
*/

Animal::Animal() : _type( "Animal" )
{
	std::cout	<< "Default constructor for Animal as been called"
				<< std::endl;
}

Animal::Animal( const Animal& other )
{
	*this = other;
	std::cout	<< "Copy constructor for Animal as been called"
				<< std::endl;
}

Animal::~Animal()
{
	std::cout	<< "Destructor for Animal as been called"
				<< std::endl;
}

Animal&	Animal::operator=( const Animal& other )
{
	std::cout	<< "Copy assignment operator called"
				<< std::endl;
	if (this != &other)
		_type = other.getType();
	return( *this );
}

std::string	Animal::getType() const
{
	return ( _type );
}

void		Animal::makeSound() const
{}
