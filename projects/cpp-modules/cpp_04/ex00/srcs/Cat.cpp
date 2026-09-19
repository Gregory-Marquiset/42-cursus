//-------> ./srcs.Cat.cpp <-------//

# include "../includes/Cat.hpp"

/*
class Cat : public Animal
{
	public:
		Cat();
		Cat( const Cat& copy );
		~Cat();
		Cat&	operator=( const Cat& other );

		//-------> Animal methode <-------//
		void		makeSound() const;
};
*/

Cat::Cat() : Animal()
{
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
	}
	return( *this );
}

//-------> Animal methode <-------//

void	Cat::makeSound() const
{
	std::cout	<< "This " << _type << " make a Miaou"
				<< std::endl;
}
