/* Demo de ft_printf : chaque ligne est imprimee par ft_printf puis par printf, avec la valeur de retour */
#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

#define CMP(...) do { \
	int a, b; \
	fflush(stdout); a = ft_printf("  ft_printf : " __VA_ARGS__); \
	fflush(stdout); b = printf("  printf    : " __VA_ARGS__); \
	fflush(stdout); printf("  retours %d / %d %s\n\n", a, b, a == b ? "OK" : "KO"); \
} while (0)

int	main(void)
{
	CMP("%c|%s|%d|%i|%u\n", '4', "deux", INT_MIN, 42, UINT_MAX);
	CMP("%x|%X|%p|%%\n", 3735928559u, 48879, (void *)0x42);
	CMP("[%-8d] [%08d] [%.3s] [%+d] [% d] [%#x]\n", 42, -42, "tronque", 42, 42, 255);
	CMP("%s|%p\n", (char *)NULL, NULL);
	return (0);
}
