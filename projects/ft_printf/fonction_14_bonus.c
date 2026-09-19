/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_14_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:35:11 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/20 01:53:10 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_espace_p(unsigned long long adrs)
{
	int	i;

	i = 0;
	if (adrs > 0)
		i += put_char(' ');
	i += adress(adrs);
	return (i);
}

int	zero_digit_c(int c, int n)
{
	int	i;

	i = 0;
	n -= 1;
	while (i < n)
		i += put_char(' ');
	return (i += put_char(c));
}

int	zero_digit_s(char *str, int n)
{
	int	i;

	i = 0;
	n -= len_str(str);
	while (i < n)
		i += put_char(' ');
	return (i += put_str(str));
}

int	put_plus_p(unsigned long long adrs)
{
	int	i;

	i = 0;
	if (adrs > 0)
		i += put_char('+');
	i += adress(adrs);
	return (i);
}

int	minus_digit_dot_c(int c, int n)
{
	int	i;

	i = 0;
	i += put_char(c);
	n -= 1;
	while (n-- > 0 && (!c || c))
		i += put_char(' ');
	return (i);
}
