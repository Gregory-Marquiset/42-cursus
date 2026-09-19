//-------> ./includes/Animal.hpp <-------//

# ifndef ANIMAL_HPP
#define ANIMAL_HPP

# include <iostream>
# include "Brain.hpp"

class Animal
{
	protected:
		std::string	_type;
	public:
		Animal();
		Animal( const Animal& copy );
		virtual	~Animal();
		Animal&	operator=( const Animal& other );

		//-------> Self methode <-------//
		std::string		getType() const;
		virtual void	makeSound() const;
};

#endif	// ANIMAL_HPP
