//-------> ./includes/BitcoinExchange.hpp <-------//

#ifndef BITCOINEXCHANGE_CPP
#define BITCOINEXCHANGE_CPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class	BtcExchange
{
	private:
		std::map<std::string, float>	_DataBase;
		bool	LoadDatabase(const std::string& DataBaseFile);
		bool	ReadInputFile(const std::string& InputFile) const;

	public:
		BtcExchange();
		BtcExchange(const std::string& DataBaseFile, const std::string& InputFile);
		BtcExchange(const BtcExchange& Other);
		~BtcExchange();
		BtcExchange&	operator=(const BtcExchange& Other);

		class	BadInputFileException : public std::exception
		{
			const char* what() const throw();
		};
		class	EmptyDataBaseException : public std::exception
		{
			const char*	what() const throw();
		};
};

#endif //	BITCOINEXCHANGE_CPP
