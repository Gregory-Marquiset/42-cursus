/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_15_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:38:59 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/20 04:36:04 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_dot_digit_x(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (n1-- > 0)
			i += put_char(' ');
		return (i);
	}
	if (n2 > len_hexa(nbr))
		n1 -= n2;
	else if (n2 <= len_hexa(nbr))
		n1 -= len_hexa(nbr);
	n2 -= len_hexa(nbr);
	while (i < n1)
		i += put_char(' ');
	while (n2-- > 0)
		i += put_char('0');
	return (i += conv_hexa_lowercase(nbr));
}

int	digit_dot_digit_uppx(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (n1-- > 0)
			i += put_char(' ');
		return (i);
	}
	if (n2 > len_hexa(nbr))
		n1 -= n2;
	else if (n2 <= len_hexa(nbr))
		n1 -= len_hexa(nbr);
	n2 -= len_hexa(nbr);
	while (i < n1)
		i += put_char(' ');
	while (n2-- > 0)
		i += put_char('0');
	return (i += conv_hexa_uppercase(nbr));
}

int	minus_digit_dot_digit_c(int c, int n1, int n2)
{
	int	i;

	i = 0;
	if (n1 == 1 && n2 == 0)
		return (put_char(c));
	if (!c)
		n1 -= 1;
	if (n1 <= 1)
	{
		i += put_char(c);
		while (n2 < n1--)
			i += put_char(' ');
		return (i);
	}
	if (n2 > 1)
		n1 -= 1;
	else if (n2 <= 1 && c)
		n1 -= 1;
	i += put_char(c);
	while (n1-- > 0)
		i += put_char(' ');
	return (i);
}

int	dot_zero_flag(char *str, long long nbr)
{
	if (*str == 'd' || *str == 'i')
		return (put_nbr((int)nbr));
	else if (*str == 'u')
		return (put_nbr((unsigned int)nbr));
	else if (*str == 'p')
		return (adress((unsigned long long)nbr));
	else if (*str == 'x')
		return (conv_hexa_lowercase((unsigned)nbr));
	else if (*str == 'X')
		return (conv_hexa_uppercase((unsigned)nbr));
	return (0);
}

int	dot_p(va_list args, int n)
{
	int				i;
	int				len;
	unsigned int	nbr;

	i = 0;
	len = 0;
	nbr = va_arg(args, unsigned long long);
	if (nbr == 0)
		return (put_str("(nil)"));
	n -= len_hexa(nbr);
	i += put_char('0');
	i += put_char('x');
	while (len < n)
	{
		i += put_char('0');
		len++;
	}
	return (i + conv_hexa_lowercase(nbr));
}
