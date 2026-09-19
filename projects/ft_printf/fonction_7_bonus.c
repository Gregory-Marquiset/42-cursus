/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_7_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 05:33:20 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 01:56:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_flag_space(va_list args, char *str, int nbr)
{
	if (*str == 'c')
		return (space_c(args, nbr));
	else if (*str == 's')
		return (space_s(args, nbr));
	else if (*str == 'd' || *str == 'i')
		return (space_di(args, nbr));
	else if (*str == 'u')
		return (space_u(args, nbr));
	else if (*str == 'p')
		return (space_p(args, nbr));
	else if (*str == 'x')
		return (space_x(args, nbr));
	else if (*str == 'X')
		return (space_uppx(args, nbr));
	return (0);
}

int	dot_digit(va_list args, char *str)
{
	int	nbr;

	nbr = 0;
	nbr = a_to_i(str);
	while (is_digit(*str) || *str == '0')
		str++;
	if (is_flag(*str))
		return (dot_digit_flag(args, str, nbr));
	return (0);
}

int	digit_dot(va_list args, char *str, int nbr)
{
	if (*str == 'c')
		return (digit_dot_digit_c(va_arg(args, int), nbr, 0));
	else if (*str == 's')
		return (digit_dot_digit_s(va_arg(args, char *), nbr, 0));
	else if (*str == 'd' || *str == 'i')
		return (digit_dot_digit_diu(va_arg(args, int), nbr, 0));
	else if (*str == 'u')
		return (digit_dot_digit_diu(va_arg(args, unsigned int), nbr, 0));
	else if (*str == 'p')
		return (digit_dot_p(va_arg(args, unsigned long long), nbr));
	else if (*str == 'x')
		return (digit_dot_digit_x(va_arg(args, unsigned), nbr, 0));
	else if (*str == 'X')
		return (digit_dot_digit_uppx(va_arg(args, unsigned), nbr, 0));
	else if (is_digit(*str) || *str == '0')
		return (digit_dot_digit(args, str, nbr));
	return (0);
}

int	dot_digit_flag(va_list args, char *str, int nbr)
{
	if (*str == 'c')
		return (put_char(va_arg(args, int)));
	if (*str == 's')
		return (dot_s(args, nbr));
	else if (*str == 'd' || *str == 'i')
		return (dot_di(args, nbr));
	else if (*str == 'u')
		return (dot_u(args, nbr));
	else if (*str == 'p')
		return (dot_p(args, nbr));
	else if (*str == 'x')
		return (dot_x(args, nbr));
	else if (*str == 'X')
		return (dot_uppx(args, nbr));
	return (0);
}

int	dot_zero(va_list args, char *str)
{
	long long	nbr;

	while (*str == '0')
		str++;
	if (*str == 'c')
		return (put_char(va_arg(args, int)));
	if (is_digit(*str))
		return (dot_zero_digit(args, str));
	nbr = va_arg(args, int);
	if (*str != 'p' && nbr > -1 && nbr < 1)
		return (0);
	if (is_flag(*str) && !(*str == 's'))
		return (dot_zero_flag(str, nbr));
	return (0);
}
