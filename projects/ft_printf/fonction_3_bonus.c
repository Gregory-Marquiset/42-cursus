/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:30:54 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 03:05:13 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_digit_dot_digit_x(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (i < n1)
			i += put_char(' ');
		return (i);
	}
	n2 -= len_hexa(nbr);
	while (n2-- > 0)
		i += put_char('0');
	i += conv_hexa_lowercase(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_digit_uppx(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (i < n1)
			i += put_char(' ');
		return (i);
	}
	n2 -= len_hexa(nbr);
	while (n2-- > 0)
		i += put_char('0');
	i += conv_hexa_uppercase(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_digit_s(char *str, int n1, int n2)
{
	int	i;

	i = 0;
	if (n1 <= len_str(str))
	{
		i += put_str_n(str, n2);
		if (n2 < 6 && !str)
		{
			while (n1-- > 0)
				i += put_char(' ');
			return (i);
		}
		while (n2 < n1--)
			i += put_char(' ');
		return (i);
	}
	if (n2 > len_str(str))
		n1 -= len_str(str);
	else if (n2 <= len_str(str) && str)
		n1 -= n2;
	i += put_str_n(str, n2);
	while (n1-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_di(long long nbr, int n)
{
	int	i;

	i = 0;
	if (n == 0 && nbr == 0)
		return (0);
	if (nbr != 0)
	{
		if (n < 0)
			return (i += put_nbr(nbr));
		i += put_nbr(nbr);
	}
	if (nbr != 0)
		n -= len_nbr(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_u(unsigned int nbr, int n)
{
	int	i;

	i = 0;
	if (n == 0 && nbr == 0)
		return (0);
	if (nbr != 0)
	{
		i += put_nbr(nbr);
		n--;
	}
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}
