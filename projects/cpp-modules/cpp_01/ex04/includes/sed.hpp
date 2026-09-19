# ifndef SED_HPP
#define SED_HPP

# include <iostream>
#include <fstream>
#include <sstream>

class	Sed
{
	public:
		static bool	replaceInFile( const std::string& filename, const std::string& s1, const std::string& s2 );
};

#endif	//SED_HPP