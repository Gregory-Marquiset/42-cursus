/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:20:52 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/06 16:54:31 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_n_mot(char const *s, char *c)
{
	int	i;
	int	nb_mot;

	i = 0;
	nb_mot = 0;
	while (s[i])
	{
		if (i == 0 && !ft_is_charset(c, s[i]))
			nb_mot++;
		else if (!ft_is_charset(c, s[i]) && ft_is_charset(c, s[i - 1]))
			nb_mot++;
		i++;
	}
	return (nb_mot);
}

static char	*remplir_dest(char const *s, int start, int end)
{
	char	*tab;
	int		i;

	tab = ft_calloc((end - start + 1), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (start < end)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	return (tab);
}

int	ft_split(char ***dest, char *s, char *c)
{
	int (i) = 0;
	int (j) = 0;
	int (start) = 0;
	if (!s)
		return (EXIT_SUCCESS);
	*dest = ft_calloc((ft_n_mot(s, c) + 1), sizeof(char *));
	if (!*dest)
		return (EXIT_FAILURE);
	while (i < ft_strlen(s))
	{
		if (s[i] && !ft_is_charset(c, s[i]))
		{
			start = i;
			while (!ft_is_charset(c, s[i]) && s[i])
				i++;
			(*dest)[j] = remplir_dest(s, start, i);
			if (!(*dest)[j])
				return (ft_destroy_tab(dest), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
