//-------> ./srcs/display.cpp <-------//

#include "../includes/display.hpp"

static std::string	itostr_cpp98(int value)
{
	std::ostringstream	oss;

	oss	<< value;
	return (oss.str());
}

static std::string	dtostr_cpp98(double value, bool exp)
{
	std::ostringstream	oss;

	if (exp == true)
		oss	<< std::fixed << std::setprecision(1) << value;
	else
		oss	<< value;
	return (oss.str());
}

static bool			isSpecialLiteral(const std::string& s)
{
	return (
		s == "nan" || s == "nanf" ||
		s == "+inf" || s == "+inff" ||
		s == "-inf" || s == "-inff" ||
		s == "inf" || s == "inff"
	);
}

void				printConv(const std::string& s, enum e_type type)
{
	std::string	strChar = "impossible";
	std::string	strInt = "impossible";
	std::string	strFloat = "impossible";
	std::string	strDouble = "impossible";

	char		cChar = 0;
	int			cInt = 0;
	float		cFloat = 0.0f;
	double		cDouble = 0.0;

	if (isSpecialLiteral(s))
	{
		if (s == "nan" || s == "nanf")
		{
			strFloat = "nanf";
			strDouble = "nan";
		}
		else if (s == "+inf" || s == "+inff" || s == "inf" || s == "inff")
		{
			strFloat = "+inff";
			strDouble = "+inf";
		}
		else if (s == "-inf" || s == "-inff")
		{
			strFloat = "-inff";
			strDouble = "-inf";
		}
	}
	else switch (type)
	{
		case CHAR_TYPE:
			cChar = s[0];
			cInt = static_cast<int>(cChar);
			cFloat = static_cast<float>(cChar);
			cDouble = static_cast<double>(cChar);

			strChar = std::isprint(cChar) ? std::string(1, cChar) : "Non displayable";
			strInt = dtostr_cpp98(cInt, false);
			strFloat = dtostr_cpp98(cFloat, true) + "f";
			strDouble = dtostr_cpp98(cDouble, true);
			break;

		case INT_TYPE:
			cInt = std::atoi(s.c_str());
			cChar = static_cast<char>(cInt);
			cFloat = static_cast<float>(cInt);
			cDouble = static_cast<double>(cInt);

			if (cInt >= 0 && cInt <= 127)
				strChar = std::isprint(cChar) ? std::string(1, cChar) : "Non displayable";
			else
				strChar = "impossible";

			strInt = itostr_cpp98(cInt);
			strFloat = dtostr_cpp98(cFloat, true) + "f";
			strDouble = dtostr_cpp98(cDouble, true);
			break;

		case FLOAT_TYPE:
			cFloat = strtof(s.c_str(), NULL);
			cInt = static_cast<int>(cFloat);
			cChar = static_cast<char>(cFloat);
			cDouble = static_cast<double>(cFloat);

			if (cFloat >= 0 && cFloat <= 127 && cFloat == static_cast<int>(cFloat))
				strChar = std::isprint(cChar) ? std::string(1, cChar) : "Non displayable";

			if (cFloat >= static_cast<float>(INT_MIN) && cFloat <= static_cast<float>(INT_MAX) && cFloat == static_cast<int>(cFloat))
				strInt = dtostr_cpp98(cInt, false);

			strFloat = dtostr_cpp98(cFloat, true) + "f";
			strDouble = dtostr_cpp98(cDouble, true);
			break;

		case DOUBLE_TYPE:
			cDouble = strtod(s.c_str(), NULL);
			cFloat = static_cast<float>(cDouble);
			cInt = static_cast<int>(cDouble);
			cChar = static_cast<char>(cDouble);

			if (cDouble >= 0 && cDouble <= 127 && cDouble == static_cast<int>(cDouble))
				strChar = std::isprint(cChar) ? std::string(1, cChar) : "Non displayable";

			if (cDouble >= static_cast<double>(INT_MIN) && cDouble <= static_cast<double>(INT_MAX) && cDouble == static_cast<int>(cDouble))
				strInt = dtostr_cpp98(cInt, false);

			strFloat = dtostr_cpp98(cFloat, true) + "f";
			strDouble = dtostr_cpp98(cDouble, true);
			break;

		default:
			break;
	}

	std::cout	<< "char: " << strChar << std::endl;
	std::cout	<< "int: " << strInt << std::endl;
	std::cout	<< "float: " << strFloat << std::endl;
	std::cout	<< "double: " << strDouble << std::endl;
}
