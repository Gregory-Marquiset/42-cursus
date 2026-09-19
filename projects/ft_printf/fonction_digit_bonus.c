/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_digit_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:33:20 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/20 01:42:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	a_to_i(char *str)
{
	int	nbr;

	nbr = 0;
	while (is_digit(*str) || *str == '0')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr);
}

int	digit(va_list args, char *str)
{
	int	nbr;

	nbr = a_to_i(str);
	while (is_digit(*str) || *str == '0')
		str++;
	if (is_flag(*str))
		return (digit_flag_space(args, str, nbr));
	else if (*str == ' ')
		return (digit_flag_space(args, str, nbr));
	else if (*str == '.')
		return (digit_dot(args, str + 1, nbr));
	return (0);
}

int	le_z(va_list args, char *str)
{
	while (*str == '0')
		str++;
	if (is_digit(*str))
		return (zero_digit(args, str));
	else if (*str == 'c')
		return (put_char(va_arg(args, int)));
	else if (*str == 's')
		return (put_str(va_arg(args, char *)));
	else if (*str == 'd' || *str == 'i')
		return (put_nbr(va_arg(args, int)));
	else if (*str == 'u')
		return (put_nbr(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (conv_hexa_lowercase(va_arg(args, unsigned)));
	else if (*str == 'X')
		return (conv_hexa_uppercase(va_arg(args, unsigned)));
	else if (*str == '.')
		return (zero_dot(args, str + 1));
	return (0);
}

int	put_str_n(char *str, int n)
{
	int	i;

	i = 0;
	if (!str && n > 5)
		return (put_str("(null)"));
	else if (!str && n < 6)
		return (0);
	while (i < n && *str)
		i += put_char(*str++);
	return (i);
}
