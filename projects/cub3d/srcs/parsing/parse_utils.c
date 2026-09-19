/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:02:50 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/06 15:22:52 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_is_charset(char *cset, char c)
{
	int	i;

	i = 0;
	if (!cset)
		return (0);
	while (cset[i])
	{
		if (cset[i] == c)
			return (1);
		i++;
	}
	return (0);
}
