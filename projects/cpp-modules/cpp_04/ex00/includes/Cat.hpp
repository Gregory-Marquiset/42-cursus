//-------> ./includes.Cat.hpp <-------//

# ifndef CAT_HPP
#define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		Cat( const Cat& copy );
		~Cat();
		Cat&	operator=( const Cat& other );

		//-------> Animal methode <-------//
		void			makeSound() const;
};

#endif	// CAT_HPP