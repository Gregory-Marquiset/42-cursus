//------------------ includes/PMERGEME.hpp ------------------//
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <sys/time.h>

template<typename Container>
void AfficherContainer(const Container& C)
{
    for (typename Container::const_iterator it = C.begin(); it != C.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
}

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);

		template<typename Container>
		PmergeMe(const std::string& input, Container& C)
		{
			if (typeid(C) != typeid(std::vector<int>) &&
				typeid(C) != typeid(std::deque<int>))
				throw InvalideContainerException();

			std::istringstream iss(input);
			std::string token;
			while (iss >> token)
			{
				if (token.empty())
					throw InvalideTokenException();
				for (size_t i = 0; i < token.size(); ++i)
					if (!std::isdigit(token[i]))
						throw InvalideTokenException();

				int v = std::atoi(token.c_str());
				if (v < 0) 
					throw NegatifIntegerException();
				if (v == 0)
					throw ZeroIntegerException();

				C.push_back(v);
			}

			fordJohnsonSort(C);
		}
		
		class	InvalideContainerException : public std::exception
		{
			const char* what() const throw();
		};
		class	InvalideTokenException : public std::exception
		{
			const char* what() const throw();
		};
		class	NegatifIntegerException : public std::exception
		{
			const char* what() const throw();
		};
		class	ZeroIntegerException : public std::exception
		{
			const char* what() const throw();
		};

	private:
		template<typename Container>
		void splitPairs(
			const Container& C,
			std::vector<std::pair<
			typename Container::value_type,
			typename Container::value_type> >& pairs,
			bool& hasLeftover,
			typename Container::value_type& leftover)
		{
			int	n = C.size();
			pairs.clear();
			hasLeftover = false;

			for (int i = 0; i + 1 < n; i += 2)
			{
				typename Container::value_type a = C[i];
				typename Container::value_type b = C[i+1];
				if (a <= b)
					pairs.push_back(std::make_pair(b, a));
				else
					pairs.push_back(std::make_pair(a, b));
			}
			if (n % 2 == 1)
			{
				hasLeftover = true;
				leftover = C[n-1];
			}
		}

		static void computeJacobsthal(std::vector<int>& J, int m)
		{
			J.clear();
			J.push_back(0);
			J.push_back(1);
			for (int k = 2; ; ++k)
			{
				int nxt = J[k-1] + 2 * J[k-2];
				if (nxt > m) break;
				J.push_back(nxt);
			}
		}

		static void computeInsertionOrder(int m, std::vector<int>& order)
		{
			std::vector<int> J;
			computeJacobsthal(J, m);
			order.clear();
			int prev = 0;

			for (size_t k = 2; k < J.size(); ++k)
			{
				int bound = J[k];
				for (int idx = bound - 1; idx >= prev; --idx)
					order.push_back(idx);
				prev = bound;
			}
			for (int idx = m - 1; idx >= prev; --idx)
				order.push_back(idx);
		}

		template<typename Container>
		void fordJohnsonSort(Container& C)
		{
			int n = C.size();
			if (n <= 1) return;

			std::vector<std::pair<
			typename Container::value_type,
			typename Container::value_type> > pairs;
			typename Container::value_type leftoverVal;
			bool hasLeftover;
			splitPairs(C, pairs, hasLeftover, leftoverVal);

			Container L;
			for (size_t i = 0; i < pairs.size(); ++i)
				L.push_back(pairs[i].first);

			fordJohnsonSort(L);

			Container sorted = L;

			int k0 = 0;
			for (size_t i = 0; i < pairs.size(); ++i)
				if (pairs[i].first == sorted[0]) { k0 = i; break; }
			sorted.insert(sorted.begin(), pairs[k0].second);

			std::vector<int> remIdx;
			for (size_t i = 0; i < pairs.size(); ++i)
				if ((int)i != k0)
					remIdx.push_back(i);
			if (hasLeftover)
				remIdx.push_back(-1);

			std::vector<int> order;
			computeInsertionOrder((int)remIdx.size(), order);

			for (size_t t = 0; t < order.size(); ++t)
			{
				int ridx = remIdx[ order[t] ];
				typename Container::value_type val;
				if (ridx < 0)
					val = leftoverVal;
				else
					val = pairs[ridx].second;

				typename Container::iterator hi;
				if (ridx >= 0)
					hi = std::upper_bound(sorted.begin(),
							sorted.end(), pairs[ridx].first);
				else
					hi = sorted.end();

				typename Container::iterator pos =
					std::lower_bound(sorted.begin(), hi, val);

				sorted.insert(pos, val);
			}

			C.swap(sorted);
		}
};

#endif // PMERGEME_HPP
