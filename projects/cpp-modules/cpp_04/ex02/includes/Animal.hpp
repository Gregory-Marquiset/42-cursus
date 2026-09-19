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

		std::string		getType() const;
		virtual void	makeSound() const = 0;
};

#endif	// ANIMAL_HPP
