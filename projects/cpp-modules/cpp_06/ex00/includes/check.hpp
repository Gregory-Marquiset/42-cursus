//-------> ./includes/check.hpp <-------//

# ifndef CHECK_HPP
#define CHECK_HPP

#include <string>
#include <cstdlib>

typedef struct	s_trimUtils
{
	std::string	trimed;
	std::size_t	i;
	std::size_t	sign;
	int			signPos;
	std::size_t	dot;
	int			dotPos;
	std::size_t	exp;
	int			expPos;
	s_trimUtils() :
		trimed(""), i(0), sign(0), signPos(-1), dot(0), dotPos(-1), exp(0), expPos(-1) {}
}	t_trimUtils;

std::string	trimString(const std::string& literal);
bool		isChar(const std::string& s);
bool		isInt(const std::string& s);
bool		isFloat(const std::string& s);
bool		isDouble(const std::string& s);

#endif	// CHECK_HPP