//-------> ./srcs.Dog.cpp <-------//

# include "../includes/Dog.hpp"

/*
class Dog : public Animal
{
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
	std::cout	<< "Destructor for Dog as been called"
				<< std::endl;
}

Dog&	Dog::operator=( const Dog& other )
{
	std::cout	<< "Copy assignment operator called"
				<< std::endl;
	if ( this != &other )
		_type = other.getType();
	return ( *this );
}

//-------> Animal methode <-------//

void		Dog::makeSound() const
{
	std::cout	<< "This " << _type << " make a Waaf"
				<< std::endl;
}
