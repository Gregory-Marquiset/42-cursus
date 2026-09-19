# include <iostream>
# include <string>

class	Weapon
{
	private:
		std::string	_type;
	public:
		Weapon( std::string Type );
		const std::string&	getType() const;
		void			setType( std::string Type );
		~Weapon();
};