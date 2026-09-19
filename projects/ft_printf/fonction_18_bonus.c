/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_18_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 00:49:15 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 02:47:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	zero_digit_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
		n -= len_adress(nbr);
	else if (nbr > 0)
		n -= len_hexa(nbr);
	if (nbr == 0 && n < len_adress(nbr))
		return (adress(nbr));
	if (nbr > 0)
		i += put_str("0x");
	while (i < n)
	{
		if (nbr > 0)
			i += put_char('0');
		else
			i += put_char(' ');
	}
	if (nbr > 0)
		return (i += conv_hexa_lowercase(nbr));
	else
		return (i += adress(nbr));
}

int	dot_zero_digit(va_list args, char *str)
{
	int	n;

	n = 0;
	n = a_to_i(str);
	while (is_digit(*str) || *str == '0')
		str++;
	if (is_flag(*str))
		return (dot_zero_digit_flag(args, str, n));
	return (0);
}

int	dot_zero_digit_flag(va_list args, char *str, int n)
{
	if (*str == 'c')
		return (put_char(va_arg(args, int)));
	if (*str == 's')
		return (dot_zero_digit_s(va_arg(args, char *), n));
	if (*str == 'd' || *str == 'i')
		return (dot_zero_digit_di(va_arg(args, int), n));
	if (*str == 'u')
		return (zero_digit_u(va_arg(args, unsigned int), n));
	if (*str == 'p')
		return (dot_zero_digit_p(va_arg(args, unsigned long long), n));
	if (*str == 'x')
		return (zero_digit_x(va_arg(args, unsigned), n));
	if (*str == 'X')
		return (zero_digit_uppx(va_arg(args, unsigned), n));
	return (0);
}

int	dot_zero_digit_s(char *str, int n)
{
	int	i;

	i = 0;
	if (n < 6 && !str)
		return (0);
	return (i += put_str_n(str, n));
}

int	dot_zero_digit_di(long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		i += put_char('-');
		nbr = -nbr;
		n -= len_nbr(nbr) - 1;
	}
	else if (nbr >= 0)
		n -= len_nbr(nbr);
	while (i < n)
		i += put_char('0');
	return (i += put_nbr(nbr));
}
