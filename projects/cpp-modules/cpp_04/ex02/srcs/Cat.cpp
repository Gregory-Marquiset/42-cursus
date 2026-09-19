//-------> ./srcs/Cat.cpp <-------//

# include "../includes/Cat.hpp"

/*
class Cat : public Animal
{
	protected:
		Brain*		_brain;
	public:
		Cat();
		Cat( const Cat& copy );
		~Cat();
		Cat&	operator=( const Cat& other );

		//-------> Animal methode <-------//
		void		makeSound() const;

		//-------> Self methode <-------//
		Brain*	Cat::getBrain() const;
};
*/

Cat::Cat() : Animal()
{
	_brain = new Brain();
	_type = "Cat";
	std::cout	<< "Default constructor for Cat as been called"
				<< std::endl;
}

Cat::Cat( const Cat& other ) : Animal( other )
{
	*this = other;
	std::cout	<< "Copy constructor for Cat as been called"
				<< std::endl;
}

Cat::~Cat()
{
	delete _brain;
	std::cout	<< "Destructor for Cat as been called"
				<< std::endl;
}

Cat&	Cat::operator=( const Cat& other )
{
	std::cout	<< "Copy assignment operator called"
				<< std::endl;
	if (this != &other)
	{
		_type = other.getType();
		_brain = new Brain();
		for ( int i = 0; i < 100 ; i++ )
			_brain->setIdea( i, other._brain->getIdea(i) );
	}
	return( *this );
}

//-------> Animal methode <-------//

void	Cat::makeSound() const
{
	std::cout	<< "This " << _type << " make a Miaou"
				<< std::endl;
}

//-------> Self methode <-------//

Brain*	Cat::getBrain() const
{
	return ( _brain );
}