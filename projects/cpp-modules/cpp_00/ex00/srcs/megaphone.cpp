# include <iostream>
# include <string>

int	main(int argc, char **argv)
{
	int	j = 0;
	int	trigger = 0;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			j = 0;
			while (argv[i][j])
			{
				std::cout << static_cast<char>(std::toupper(argv[i][j]));
				j++;
			}
		}
		if (j > 1)
		{
			std::cout << std::endl;
			trigger++;
		}
	}
	if (argc == 1 || trigger == 0)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (0);
}