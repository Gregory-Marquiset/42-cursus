/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_symbol_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:56:37 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/20 02:30:23 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sharp(va_list args, char *str)
{
	if (*str == 'X')
		return (adress_uppercase(va_arg(args, unsigned)));
	else if (*str == 'x')
		return (adress_lowercase(va_arg(args, unsigned)));
	return (reading(args, str));
}

int	space(va_list args, char *str)
{
	while (*str == ' ')
		str++;
	if (*str == 'd' || *str == 'i')
		return (put_espace_di(va_arg(args, int)));
	if (*str == 'p')
		return (put_espace_p(va_arg(args, unsigned long long)));
	return (reading(args, str));
}

int	plus(va_list args, char *str)
{
	while (*str == '+')
		str++;
	if (*str == 'd' || *str == 'i')
		return (put_plus_di(va_arg(args, int)));
	else if (*str == 'p')
		return (put_plus_p(va_arg(args, unsigned long long)));
	return (reading(args, str));
}

int	le_dot(va_list args, char *str)
{
	int	i;

	i = 0;
	if (*str == 's')
		return (0);
	if (*str == '0')
		return (dot_zero(args, str + 1));
	if (is_digit(*str))
		return (dot_digit(args, str));
	if (is_flag(*str))
		return (redirection_dot(args, str));
	return (i);
}

int	minus(va_list args, char *str)
{
	int	nbr;

	while (*str == '-')
		str++;
	if (*str == '.')
		return (minus_dot(args, str + 1));
	nbr = a_to_i(str);
	while (is_digit(*str) || *str == '0' || *str == '-')
		str++;
	if (is_flag(*str))
		return (minus_flag(args, str, nbr));
	else if (*str == '.')
		return (minus_digit_dot(args, str + 1, nbr));
	return (0);
}
