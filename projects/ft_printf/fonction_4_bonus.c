/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:30:54 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 01:38:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_digit_dot_x(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr != 0)
	{
		i += conv_hexa_lowercase(nbr);
		n -= len_hexa(nbr);
	}
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_uppx(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr != 0)
	{
		i += conv_hexa_uppercase(nbr);
		n -= len_hexa(nbr);
	}
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_digit_dot_s(char *str, int n)
{
	int	i;

	i = 0;
	while (n-- > 0 && (!str || str))
		i += put_char(' ');
	return (i);
}

int	minus_c(int c, int n)
{
	int	i;

	i = 0;
	i += put_char(c);
	n -= 1;
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}

int	minus_s(char *str, int n)
{
	int	i;

	i = 0;
	n -= len_str(str);
	i += put_str(str);
	while (n-- > 0)
		i += put_char(' ');
	return (i);
}
