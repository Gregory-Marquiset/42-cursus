/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:06:53 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/05 15:52:22 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_strndup(char **dup, char *s, int n)
{
	int		i;

	i = 0;
	if (!s)
		return (EXIT_SUCCESS);
	while (s[i] && i < n)
		i++;
	*dup = ft_calloc(i + 1, sizeof(char));
	if (!*dup)
		return (ft_err_str(ERR_MSG_MALLOC), EXIT_FAILURE);
	i = 0;
	while (s[i] && i < n)
	{
		(*dup)[i] = s[i];
		i++;
	}
	return (EXIT_SUCCESS);
}
