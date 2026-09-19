//-------> ./includes/Span.hpp <-------//

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>
#include <iterator>

class	Span
{
	private:
		std::vector<int>	_numbers;
		unsigned int		_maxSize;

	public:
		Span(unsigned int N);
		Span(const Span& other);
		~Span();

		Span&	operator=(const Span& other);

		void	addNumber(int number);

		template<typename Iterator>
		void	addNumber(Iterator begin, Iterator end)
		{
			if (std::distance(begin, end) + _numbers.size() > _maxSize)
				throw StorageFullException();
			_numbers.insert(_numbers.end(), begin, end);
		}

		int		shortestSpan() const;
		int		longestSpan() const;

		class StorageFullException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		class NotEnoughNumbersException : public std::exception
		{
			public:
				const char* what() const throw();
		};
};

#endif //	SPAN_HPP


