//-------> ./includes/Serializer.hpp <-------//

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include <string>

struct	Data
{
	std::string	info;
	int			value;
};

class	Serializer
{
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*			deserialize(uintptr_t raw);
};

#endif //	SERIALIZER_HPP
