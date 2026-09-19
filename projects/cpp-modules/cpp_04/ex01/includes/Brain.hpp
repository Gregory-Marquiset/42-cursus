//-------> ./includes/Brain.hpp <-------//

#ifndef BRAIN_CPP
# define BRAIN_CPP

#include <iostream>

class	Brain
{
	private:
		std::string	ideas[100];
	public:
		Brain();
		Brain( const Brain& copy );
		~Brain();
		Brain&	operator=( const Brain& other );

		//-------> Self methode <-------//
		std::string	getIdea( int i ) const;
		void		setIdea( int i, std::string idea );
};

#endif	// BRAIN_CPP
