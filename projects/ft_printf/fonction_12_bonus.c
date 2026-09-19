/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_12_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:33:20 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 00:48:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	zero_digit_dot_x(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
	{
		while (i < n)
			i += put_char(' ');
		return (i);
	}
	n -= len_hexa(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i += conv_hexa_lowercase(nbr));
}

int	zero_digit_dot_uppx(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
	{
		while (i < n)
			i += put_char(' ');
		return (i);
	}
	n -= len_hexa(nbr);
	while (n-- > 0)
		i += put_char(' ');
	return (i += conv_hexa_uppercase(nbr));
}

int	zero_digit_flag(va_list args, char *str, int n)
{
	if (*str == 'c')
		return (zero_digit_c(va_arg(args, int), n));
	if (*str == 's')
		return (zero_digit_s(va_arg(args, char *), n));
	if (*str == 'd' || *str == 'i')
		return (zero_digit_di(va_arg(args, int), n));
	if (*str == 'u')
		return (zero_digit_u(va_arg(args, unsigned int), n));
	if (*str == 'p')
		return (zero_digit_p(va_arg(args, unsigned long long), n));
	if (*str == 'x')
		return (zero_digit_x(va_arg(args, unsigned), n));
	if (*str == 'X')
		return (zero_digit_uppx(va_arg(args, unsigned), n));
	return (0);
}

int	zero_digit_di(long long nbr, int n)
{
	int	i;

	i = 0;
	n -= len_nbr(nbr);
	if (nbr < 0)
	{
		i += put_char('-');
		nbr = -nbr;
		n++;
	}
	while (i < n)
		i += put_char('0');
	return (i += put_nbr(nbr));
}

int	zero_digit_u(long long nbr, int n)
{
	int	i;

	i = 0;
	n -= len_nbr(nbr);
	while (i < n)
		i += put_char('0');
	return (i += put_nbr(nbr));
}
