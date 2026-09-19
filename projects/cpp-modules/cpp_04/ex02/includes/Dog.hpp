//-------> ./includes/Dog.hpp <-------//

# ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal
{
	private:
		Brain*		_brain;
	public:
		Dog();
		Dog( const Dog& copy );
		~Dog();

		Dog&	operator=( const Dog& other );

		void		makeSound( void ) const;
		Brain*		getBrain() const;
};

#endif	// DOG_HPP