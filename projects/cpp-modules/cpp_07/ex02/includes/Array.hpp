#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template<typename T>
class Array
{
	private:
		T*              _array;
		unsigned int    _size;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array& other);
		~Array();

		Array& operator=(const Array& other);
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;

		unsigned int size() const;
};

template<typename T>
Array<T>::Array() : _array(new T[0]), _size(0)
{}

template<typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]), _size(n)
{
	for (unsigned int i = 0; i < n; ++i)
		_array[i] = T();
}

template<typename T>
Array<T>::Array(const Array& other) : _array(new T[other._size]), _size(other._size)
{
	for (unsigned int i = 0; i < _size; ++i)
		_array[i] = other._array[i];
}

template<typename T>
Array<T>::~Array()
{
	delete[] _array;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		delete[] _array;
		_size = other._size;
		_array = new T[_size];
		for (unsigned int i = 0; i < _size; ++i)
			_array[i] = other._array[i];
	}
	return *this;
}

template<typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _array[index];
}

template<typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _array[index];
}

template<typename T>
unsigned int Array<T>::size() const
{
	return _size;
}


#endif // ARRAY_HPP
