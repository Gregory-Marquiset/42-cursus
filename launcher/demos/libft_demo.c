/* Demo de la libft : quelques fonctions de chaque partie, appelees depuis ./cursus libft */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	const char	*s = argc > 1 ? argv[1] : "  42 Paris, Born2code, libft  ";
	char		*trim = ft_strtrim(s, " ");
	char		**words = ft_split(trim, ',');
	t_list		*lst = NULL;
	char		*n;
	int			i;

	printf("ft_strtrim(\"%s\") -> \"%s\"\n", s, trim);
	printf("ft_split(..., ',') :\n");
	for (i = 0; words[i]; i++)
	{
		printf("  [%d] \"%s\"\n", i, words[i]);
		ft_lstadd_back(&lst, ft_lstnew(words[i]));
	}
	printf("ft_lstsize -> %d\n", ft_lstsize(lst));
	n = ft_itoa(-2147483648);
	printf("ft_itoa(INT_MIN) -> \"%s\"\n", n);
	printf("ft_atoi(\"  -0042abc\") -> %d\n", ft_atoi("  -0042abc"));
	ft_lstclear(&lst, free);
	free(words);
	free(trim);
	free(n);
	return (0);
}
