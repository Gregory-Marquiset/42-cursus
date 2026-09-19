/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:39:00 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:52:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_calc_max_len(t_cub *cub, char *line, char *charset, int end)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && ft_is_charset(charset, line[i]) && i < end)
	{
		i++;
		if (line[i] == '\t')
			len += 4;
		else
			len++;
	}
	if (len > cub->parse->len_max)
		cub->parse->len_max = len;
	return (0);
}

static int	ft_parse_map(t_cub *cub, char *line)
{
	int (i) = 0;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	while (line[i] && ft_is_charset("01NSEWCO \t", line[i]))
	{
		if (ft_is_charset("NSEW", line[i]))
		{
			if (cub->parse->player != 0)
				return (ft_err_str(ERR_MSG_PLAYER), -1);
			cub->parse->player++;
		}
		i++;
	}
	while (ft_is_whitespace(line[i]))
		i++;
	if (line[i] != '\0')
		return (ft_err_2str(ERR_MSG_INVALID, line), -1);
	while (ft_is_whitespace(line[i - 1]))
		i--;
	return (ft_calc_max_len(cub, line, "01NSEWCO \t", i));
}

int	ft_is_mapline(t_cub *cub, char *line, int n)
{
	if (cub->parse->map_start == 0)
		cub->parse->map_start = n;
	cub->parse->last_map_line = n;
	return (ft_parse_map(cub, line));
}
