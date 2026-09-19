//-------> ./srcs/Span.cpp <-------//

#include "../includes/Span.hpp"
#include <limits>
#include <cstdlib>

Span::Span(unsigned int N) : _maxSize(N)
{}

Span::Span(const Span& other) : _numbers(other._numbers), _maxSize(other._maxSize)
{}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return (*this);
}

Span::~Span()
{}

void Span::addNumber(int n)
{
    if (_numbers.size() >= _maxSize)
        throw Span::StorageFullException();
    _numbers.push_back(n);
}

int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw Span::NotEnoughNumbersException();

    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = std::numeric_limits<int>::max();
    for (size_t i = 0; i < sorted.size() - 1; ++i)
    {
        int diff = sorted[i + 1] - sorted[i];
        if (diff < minSpan)
            minSpan = diff;
    }
    return (minSpan);
}

int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw Span::NotEnoughNumbersException();

    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return (max - min);
}

// Exceptions

const char* Span::StorageFullException::what() const throw()
{
    return ("Cannot add more elements: storage is full.");
}

const char* Span::NotEnoughNumbersException::what() const throw()
{
	return ("Not enough numbers to compute span!");
}