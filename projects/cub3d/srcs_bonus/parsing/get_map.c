/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:46 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:57:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_get_map_line(t_cub *cub, char *line, int *index)
{
	int	i;

	i = 0;
	(*index)++;
	cub->map[*index] = ft_calloc(cub->parse->len_max + 2, sizeof(char));
	if (!cub->map[*index])
		return (ft_err_str(ERR_MSG_MALLOC), -1);
	while (line[i] && i < cub->parse->len_max)
	{
		if (ft_strchr("NSEW", line[i]))
			ft_set_player_position(cub, i, *index, line[i]);
		else if (line[i] == '\t')
			ft_handle_tab(cub, &i, *index);
		else
			ft_fill_map_char(cub, line[i], i, *index);
		i++;
	}
	ft_complete_map(cub, i, index);
	return (0);
}

static int	ft_is_map_closed_2(t_cub *cub, int i, int j)
{
	if (i == 0)
	{
		if (!ft_is_charset("19", cub->map[i][j]) || \
		(cub->map[i][j] == '9' && cub->map[i + 1][j] == '0'))
			return (-1);
	}
	else if (!cub->map[i + 1])
	{
		if (!ft_is_charset("19", cub->map[i][j]) || \
		(cub->map[i][j] == '9' && cub->map[i - 1][j] == '0'))
			return (-1);
	}
	else
	{
		if (cub->map[i][j] == '9' && ((cub->map[i][j + 1] != '\0'\
		&& !ft_is_charset("19", cub->map[i][j + 1])) || \
		!ft_is_charset("19", cub->map[i][j - 1]) || \
		!ft_is_charset("19", cub->map[i - 1][j]) || \
		!ft_is_charset("19", cub->map[i + 1][j])))
			return (-1);
	}
	return (0);
}

static int	ft_is_map_closed(t_cub *cub)
{
	int (i) = -1;
	int (j) = 1;
	while (cub->map[++i])
	{
		j = 1;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'C' || cub->map[i][j] == 'O')
			{
				if (cub->map[i][j + 1] == '9' || cub->map[i][j - 1] == '9' || \
				cub->map[i + 1][j] == '9' || cub->map[i - 1][j] == '9')
					return (ft_err_str(ERR_MSG_MAP_OPEN), -1);
			}
			if (ft_is_map_closed_2(cub, i, j) != 0)
				return (ft_err_str(ERR_MSG_MAP_OPEN), -1);
			j++;
		}
	}
	return (0);
}

int	ft_get_map(t_cub *cub, int fd)
{
	char	*line;

	int (i) = 0;
	int (index) = -1;
	cub->map = ft_calloc(cub->parse->numb_of_line + 2, sizeof(char *));
	if (!cub->map)
		return (ft_err_str(ERR_MSG_MALLOC), -1);
	while (true)
	{
		line = gnl(fd);
		if (!line)
			return (free(line), ft_err_str(ERR_MSG_MALLOC), -1);
		if (line[0] == '\0')
			break ;
		if (i >= cub->parse->map_start)
		{
			if (ft_get_map_line(cub, line, &index) == -1)
				return (free(line), -1);
		}
		free(line);
		i++;
	}
	free(line);
	close(fd);
	return (ft_is_map_closed(cub));
}
