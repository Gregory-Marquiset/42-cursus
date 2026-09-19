/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:30:54 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 01:35:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_dot_digit_flag(va_list args, char *str, int n1, int n2)
{
	if (*str == 'c')
		return (digit_dot_digit_c(va_arg(args, int), n1, n2));
	else if (*str == 's')
		return (digit_dot_digit_s(va_arg(args, char *), n1, n2));
	else if (*str == 'd' || *str == 'i')
		return (digit_dot_digit_diu(va_arg(args, int), n1, n2));
	else if (*str == 'u')
		return (digit_dot_digit_diu(va_arg(args, unsigned int), n1, n2));
	else if (*str == 'p')
		return (digit_dot_digit_p(va_arg(args, unsigned), n1, n2));
	else if (*str == 'x')
		return (digit_dot_digit_x(va_arg(args, unsigned), n1, n2));
	else if (*str == 'X')
		return (digit_dot_digit_uppx(va_arg(args, unsigned), n1, n2));
	return (0);
}

int	minus_digit_dot(va_list args, char *str, int n)
{
	if (is_digit(*str) || *str == '0')
		return (minus_digit_dot_digit(args, str, n));
	else if (*str == 'c')
		return (minus_digit_dot_c(va_arg(args, int), n));
	else if (*str == 's')
		return (minus_digit_dot_s(va_arg(args, char *), n));
	else if (*str == 'd' || *str == 'i')
		return (minus_digit_dot_di(va_arg(args, int), n));
	else if (*str == 'u')
		return (minus_digit_dot_u(va_arg(args, unsigned int), n));
	else if (*str == 'p')
		return (minus_digit_dot_p(va_arg(args, unsigned long long), n));
	else if (*str == 'x')
		return (minus_digit_dot_x(va_arg(args, unsigned), n));
	else if (*str == 'X')
		return (minus_digit_dot_uppx(va_arg(args, unsigned), n));
	return (0);
}

int	minus_digit_dot_digit(va_list args, char *str, int n1)
{
	int	n2;

	n2 = a_to_i(str);
	while (is_digit(*str) || *str == '0')
		str++;
	if (*str == 'c')
		return (minus_digit_dot_digit_c(va_arg(args, int), n1, n2));
	if (*str == 's')
		return (minus_digit_dot_digit_s(va_arg(args, char *), n1, n2));
	else if (*str == 'd' || *str == 'i')
		return (minus_digit_dot_digit_di(va_arg(args, int), n1, n2));
	else if (*str == 'u')
		return (minus_digit_dot_digit_u(va_arg(args, unsigned int), n1, n2));
	else if (*str == 'p')
		return (minus_digit_dot_digit_p(va_arg(args, unsigned long long), n1,
				n2));
	else if (*str == 'x')
		return (minus_digit_dot_digit_x(va_arg(args, unsigned), n1, n2));
	else if (*str == 'X')
		return (minus_digit_dot_digit_uppx(va_arg(args, unsigned), n1, n2));
	return (0);
}

int	minus_digit_dot_digit_di(long long nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (i < n1)
			i += put_char(' ');
		return (i);
	}
	n2 -= len_nbr(nbr);
	if (nbr < 0)
	{
		nbr = -nbr;
		i += put_char('-');
		n2++;
	}
	while (n2-- > 0)
		i += put_char('0');
	i += put_nbr(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_digit_u(unsigned int nbr, int n1, int n2)
{
	int	i;

	i = 0;
	if (n2 == 0 && nbr == 0)
	{
		while (i < n1)
			i += put_char(' ');
		return (i);
	}
	n2 -= len_nbr(nbr);
	while (n2-- > 0)
		i += put_char('0');
	i += put_nbr(nbr);
	while (i < n1)
		i += put_char(' ');
	return (i);
}
