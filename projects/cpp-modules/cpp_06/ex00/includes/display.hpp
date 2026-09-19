//-------> ./includes/display.hpp <-------//

# ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cfloat>

enum	e_type
{
	CHAR_TYPE,
	INT_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	UNKNOWN_TYPE
};

void printConv(const std::string& s, enum e_type type);

#endif	// DISPLAY_HPP