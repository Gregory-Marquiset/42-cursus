//-------> ./srcs/check.cpp <-------//

#include "../includes/check.hpp"

static bool		checkTrim(t_trimUtils& u, const std::string& literal)
{
	if (u.i != literal.size())
		return (false);
	if (u.sign > 1 || u.dot > 1 || u.exp > 1)
		return (false);

	if (u.sign == 1 && u.signPos > 0)
		return (false);

	if (u.expPos > -1 && u.dotPos > u.expPos)
		return (false);

	if (literal.size() > 1 && (u.dotPos == 0 || u.expPos == 0))
		return (false);

	if (u.sign == 1 &&
		((u.dot == 1 && u.dotPos == 1) || (u.exp == 1 && u.expPos == 1)))
		return (false);

	if ((u.exp == 1 && u.trimed.length() > 1 && u.expPos == (int)u.trimed.length() - 1) ||
		(u.dot == 1 && u.trimed.length() > 1 && u.dotPos == (int)u.trimed.length() - 1))
		return (false);

	if (u.dot == 1 && u.exp == 1 && u.expPos == u.dotPos + 1)
		return (false);

	return (true);
}

std::string		trimString(const std::string& literal)
{
	t_trimUtils	u;

	if (literal.size() == 1)
	{
		u.trimed += literal[0];
		return (u.trimed);
	}
	while (u.i < literal.size() && std::isspace(literal[u.i]))
		u.i++;
	while (u.i < literal.size() && !std::isspace(literal[u.i]))	
	{
		if (literal[u.i] == '+' || literal[u.i] == '-')
		{
			u.sign++;
			u.signPos = u.trimed.length();
		}
		else if (literal[u.i] == '.')
		{
			u.dot++;
			u.dotPos = u.trimed.length();
		}
		else if (literal[u.i] == 'e' || literal[u.i] == 'E')
		{
			u.exp++;
			u.expPos = u.trimed.length();
			if (literal[u.i + 1] && (literal[u.i + 1] == '+' || literal[u.i + 1] == '-'))
				u.i++;
		}
		u.trimed += literal[u.i];
		u.i++;
	}
	while (u.i < literal.size() && std::isspace(literal[u.i]))
		u.i++;
	if (checkTrim(u, literal))
		return (u.trimed);
	else
		return ("");
}

bool			isChar(const std::string& s)
{
	if (s.length() == 1 && std::isprint(s[0]) && !std::isdigit(s[0]))
		return (true);
	return (false);
}

bool			isInt(const std::string& s)
{
	std::size_t	i = 0;
	long		testConvL = 0;

	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	if (i == s.length() && s[i] == '0')
		return (true);
	for (std::size_t idx = i; idx < s.length(); ++idx)
		if (!std::isdigit(s[idx]) || idx - i > 10)
			return (false);
	testConvL = std::atol(s.c_str());
	if (testConvL > 2147483647 || testConvL < -2147483648)
		return (false);
	return (true);
}

bool			isFloat(const std::string& s)
{
	if (s == "nanf" || s == "+inff" || s == "-inff")
		return (true);
	if (s[s.length() - 1] != 'f')
		return (false);
	if (s[s.length() - 2] == '.' || s[s.length() - 2] == 'e' || s[s.length() - 2] == 'E'
			|| s[s.length() - 2] == '+' || s[s.length() - 2] == '-')
		return (false);
	
	std::size_t	i = 0;

	if (s[i] == '+' || s[i] == '-')
		i++;
	for (std::size_t idx = i; idx < s.length() - 1; idx++)
	{
		if (!std::isdigit(s[idx]) && s[idx] != '.' && s[idx] != 'e' && s[idx] != 'E' && s[idx] != '-' && s[idx] != '+')
			return (false);
	}
	return (true);
}

bool			isDouble(const std::string& s)
{
	if (s == "nan" || s == "+inf" || s == "-inf")
		return (true);
	if (s[s.length() - 1] == '.' || s[s.length() - 1] == 'e' || s[s.length() - 1] == 'E'
			|| s[s.length() - 1] == '+' || s[s.length() - 1] == '-')
		return (false);
	if (s.find('.') == std::string::npos && s.find('e') == std::string::npos && s.find('E') == std::string::npos)
		return (false);

	std::size_t	i = 0;

	if (s[i] == '+' || s[i] == '-')
		i++;
	for (std::size_t idx = i; idx < s.length() - 1; idx++)
	{
		if (!std::isdigit(s[idx]) && s[idx] != '.' && s[idx] != 'e' && s[idx] != 'E' && s[idx] != '-' && s[idx] != '+')
			return (false);
	}
	return (true);
}
