/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_19_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 02:45:50 by gmarquis          #+#    #+#             */
/*   Updated: 2023/12/21 02:49:37 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dot_zero_digit_p(unsigned long long nbr, int n)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (adress(nbr));
	else if (nbr > 0)
		n -= len_hexa(nbr);
	if (nbr == 0 && n < len_adress(nbr))
		return (adress(nbr));
	if (nbr > 0)
	{
		i += put_str("0x");
		n += 2;
	}
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
