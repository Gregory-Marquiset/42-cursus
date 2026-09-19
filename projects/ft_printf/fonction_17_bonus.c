/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_17_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:40:30 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 01:33:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_dot_digit_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (put_str("(nil)"));
	n -= len_hexa(nbr);
	if (n <= 0)
		return (i += adress(nbr));
	i += put_str("0x");
	while (n-- > 0)
		i += put_char('0');
	i += conv_hexa_lowercase(nbr);
	return (i);
}

int	digit_dot_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (n <= len_adress(nbr))
		n -= len_adress(nbr);
	n -= len_adress(nbr);
	while (i < n)
		i += put_char(' ');
	if (nbr == 0)
		return (digit_dot_digit_p2(i, n));
	i += put_str("0x");
	return (i += conv_hexa_lowercase(nbr));
}

int	zero_digit_dot_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	n -= len_adress(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i += adress(nbr));
}

int	zero_digit_dot_digit_p(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 <= 0 || n2 < len_adress(nbr))
		n1 -= len_adress(nbr);
	else if (n2 > 0)
	{
		if (nbr > 0)
			n1 -= 2;
		n1 -= n2;
	}
	while (i < n1)
		i += put_char(' ');
	if (nbr == 0)
		return (i += adress(nbr));
	i += put_str("0x");
	n2 -= len_hexa(nbr);
	while (n2-- > 0)
		i += put_char('0');
	i += conv_hexa_lowercase(nbr);
	return (i);
}

int	zero_digit_dot_zero_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
	{
		n -= len_adress(nbr);
		while (i < n)
			i += put_char(' ');
		return (i += adress(nbr));
	}
	n -= len_adress(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i += adress(nbr));
}
