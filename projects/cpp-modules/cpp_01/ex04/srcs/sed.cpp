# include <../includes/sed.hpp>

bool	Sed::replaceInFile( const std::string& filename,
			const std::string& s1, const std::string& s2 )
{
	if (s1.empty() || s2.empty())
	{
		std::cerr << "Error : No empty string allow." << std::endl;
		return (false);
	}
	std::ifstream	infile( filename.c_str() );
	if (!infile)
	{
		std::cerr << "Error : filename or right invalid for: " << filename << std::endl;
		return (false);
	}

	std::ofstream	outfile(( filename + ".replace" ).c_str() );
	if (!outfile)
	{
		std::cerr << "Error : creation of " << filename << ".replace imposible." << std::endl;
		infile.close();
		return (false);
	}
	std::string	line = "";
	size_t		pos = 0;
	while (std::getline( infile, line ))
	{
		pos = 0;
		while ((pos = line.find( s1, pos )) != std::string::npos)
		{
			line.erase( pos, s1.length() );
			line.insert( pos, s2 );
			pos += s2.length();
		}
		outfile << line << std::endl;
	}
	infile.close();
	outfile.close();
	return (true);
}