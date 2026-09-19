//-------> ./includes.Character.hpp <-------//

# ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "interface/ICharacter.hpp"
#include "AMateria.hpp"

class	Character : public	ICharacter
{
	private:
		std::string	_name;
		AMateria*	_inventory[4];
		int			_index;
		AMateria**	_floor;
	public:
		Character();
		Character( const Character& other );
		Character( const std::string& name );
		~Character();
		Character&	operator=( const Character& other );

		//-------> ICharacter interface <-------//
		const std::string&	getName() const;
		void				equip( AMateria* m );
		void				unequip( int idx );
		void				use( int idx, ICharacter& target );

		//-------> Self methode <-------//
		void				setName( const std::string& name );
		void				showInventory( void ) const;
};

#endif // CHARACTER_HPP
