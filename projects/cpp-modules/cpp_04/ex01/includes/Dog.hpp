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

		//-------> Animal methode <-------//
		void		makeSound() const;

		//-------> Self methode <-------//
		Brain*	getBrain() const;
};

#endif	// DOG_HPP
