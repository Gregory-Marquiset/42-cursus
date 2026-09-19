//-------> ./srcs/Dog.cpp <-------//

# include "../includes/Dog.hpp"

/*
class Dog : public Animal
{
	protected:
		Brain*		_brain;
	public:
		Dog();
		Dog( const Dog& copy );
		~Dog();
		Dog&	operator=( const Dog& other );

		//-------> Animal methode <-------//
		void		makeSound() const;
};
*/

Dog::Dog() : Animal()
{
	_type = "Dog";
	_brain = new Brain();
	std::cout	<< "Default constructor for Dog as been called"
				<< std::endl;
}

Dog::Dog( const Dog& other ) : Animal( other )
{
	*this = other;
	std::cout	<< "Copy constructor for Dog as been called"
				<< std::endl;
}

Dog::~Dog()
{
	delete _brain;
	std::cout	<< "Destructor for Dog as been called"
				<< std::endl;
}

Dog&	Dog::operator=( const Dog& other )
{
	std::cout	<< "Copy assignment operator called"
				<< std::endl;
	if ( this != &other )
	{
		_type = other.getType();
		_brain = new Brain();
		for ( int i = 0; i < 100;i++ )
			_brain->setIdea( i, other._brain->getIdea( i ) );
	}
	return ( *this );
}

//-------> Animal methode <-------//

void		Dog::makeSound() const
{
	std::cout	<< "This " << _type << " make a Waaf"
				<< std::endl;
}

//-------> Self methode <-------//

Brain*	Dog::getBrain() const
{
	return ( _brain );
}