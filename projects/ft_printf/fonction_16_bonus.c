/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_16_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 04:36:10 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/20 23:39:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_dot_digit_p(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (n1-- > 0)
			i += put_char(' ');
		return (i);
	}
	if (n2 > len_adress(nbr))
		n1 -= n2;
	else if (n2 <= len_adress(nbr))
		n1 -= len_adress(nbr);
	n2 -= len_hexa(nbr);
	while (i + 2 < n1)
		i += put_char(' ');
	if (nbr == 0)
		return (digit_dot_digit_p2(i, n1));
	i += put_str("0x");
	while (n2-- > 0)
		i += put_char('0');
	return (i += conv_hexa_lowercase(nbr));
}

int	digit_dot_digit_p2(int i, int n)
{
	while (i < n)
		i += put_char(' ');
	return (i += put_str("(nil)"));
}

int	zero_dot_digit_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (n == 0 && nbr == 0)
		return (0);
	if (nbr == 0)
		return (put_str("(nil)"));
	n -= len_hexa(nbr);
	i += put_str("0x");
	while (n-- > 0)
		i += put_char('0');
	i += conv_hexa_lowercase(nbr);
	return (i);
}

int	minus_digit_dot_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	i += adress(nbr);
	n -= len_adress(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_digit_p(unsigned long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (nbr > 0)
	{
		n2 -= len_hexa(nbr);
		i += put_str("0x");
	}
	else if (nbr == 0)
	{
		i += adress(nbr);
		n2 = 0;
	}
	while (n2-- > 0)
		i += put_char('0');
	if (nbr > 0)
		i += conv_hexa_lowercase(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i);
}
