//-------> ./includes/Cat.hpp <-------//

# ifndef CAT_HPP
#define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
	private:
		Brain*		_brain;
	public:
		Cat();
		Cat( const Cat& copy );
		~Cat();

		Cat& operator=( const Cat& other );

		void		makeSound() const;
		Brain*		getBrain() const;
};

#endif	// CAT_HPP