//-------> ./srcs/Main.cpp <-------//

#include "../includes/PmergeMe.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr	<< "Error: must have two arguments." << std::endl;
		return (1);
	}

	std::string	Input = argv[1];
	if (Input.empty())
	{
		std::cerr	<< "Error: invalide user input." << std::endl;
		return (2);
	}

	long	VectorDuration;
	long	DequeDuration;
    timeval	t0, t1;

	std::vector<int>	Vector;
	try
	{
		gettimeofday(&t0, NULL);
		PmergeMe	Merge(Input, Vector);
    	gettimeofday(&t1, NULL);
		VectorDuration = (t1.tv_sec  - t0.tv_sec ) * 1000000L + (t1.tv_usec - t0.tv_usec);
	}
	catch(const std::exception& e)
	{
		std::cerr	<< "Error: " << e.what() << std::endl;
		return (3);
	}

	std::deque<int>	Deque;
	try
	{
		gettimeofday(&t0, NULL);
		PmergeMe	Merge(Input, Deque);
    	gettimeofday(&t1, NULL);
		DequeDuration = (t1.tv_sec  - t0.tv_sec ) * 1000000L + (t1.tv_usec - t0.tv_usec);
	}
	catch(const std::exception& e)
	{
		std::cerr	<< "Error: " << e.what() << std::endl;
		return (3);
	}

	std::cout	<< "Before: " << Input << std::endl;
	std::cout	<< "After:  ";
	AfficherContainer(Vector);
	std::cout	<< "Time to process a range of "	<< Vector.size()
				<< " elements with std::vector : "	<< VectorDuration
				<< " us"	<< std::endl;
	std::cout	<< "Time to process a range of "	<< Deque.size()
				<< " elements with std::deque  : "	<< DequeDuration
				<< " us"	<< std::endl;
	return (0);
}
