/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_13_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:33:20 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 01:46:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	space_digit_s(char *str, int n)
{
	int	i;

	i = 0;
	n -= len_str(str);
	while (n > 0)
	{
		i += put_char(' ');
		n--;
	}
	i += put_str(str);
	return (i);
}

int	digit_dot_digit_c(int c, int n1, int n2)
{
	int	i;

	i = 0;
	n2 = 1;
	if (n1 >= 1 && n2)
		n1--;
	while (n1-- > 0)
		i += put_char(' ');
	return (i += put_char(c));
}

int	digit_dot_digit_s(char *str, int n1, int n2)
{
	int	i;

	i = 0;
	if (n1 <= len_str(str))
	{
		if (n2 < 6 && !str)
		{
			while (n1-- > 0)
				i += put_char(' ');
			return (i);
		}
		while (n2 < n1--)
			i += put_char(' ');
		return (i += put_str_n(str, n2));
	}
	if (n2 >= len_str(str))
		n1 -= len_str(str);
	else if (n2 < len_str(str))
		if (str)
			n1 -= n2;
	while (n1-- != 0)
		i += put_char(' ');
	return (i += put_str_n(str, n2));
}

int	digit_dot_digit_diu(long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (n1-- > 0)
			i += put_char(' ');
		return (i);
	}
	if (n2 > len_nbr(nbr))
	{
		n1 -= n2;
		if (nbr < 0)
			n1--;
	}
	else if (n2 <= len_nbr(nbr))
	{
		n1 -= len_nbr(nbr);
		if (n2 == len_nbr(nbr) && nbr < 0)
			n1--;
	}
	n2 -= len_nbr(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i += digit_dot_digit_diu_2(nbr, n2));
}

int	digit_dot_digit_diu_2(long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i += put_char('-');
		n++;
	}
	while (n-- > 0)
		i += put_char('0');
	return (i += put_nbr(nbr));
}
