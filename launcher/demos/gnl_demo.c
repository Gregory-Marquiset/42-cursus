/* Demo de get_next_line : lit un fichier ligne a ligne (BUFFER_SIZE choisi a la compilation) */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd = argc > 1 ? open(argv[1], O_RDONLY) : 0;
	char	*line;
	int		n = 0;

	if (fd < 0)
		return (perror(argv[1]), 1);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	while ((line = get_next_line(fd)))
	{
		printf("%3d | %s", ++n, line);
		free(line);
	}
	printf("--- %d lignes, puis get_next_line renvoie NULL\n", n);
	return (0);
}
