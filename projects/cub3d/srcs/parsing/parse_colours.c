/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:45:37 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/13 14:22:10 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_is_number(char *colour)
{
	int	i;

	i = 0;
	while (colour[i])
	{
		if (colour[i] < '0' || colour[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_get_colours(int **colour, char **col_range)
{
	long	res;
	int		i;

	*colour = malloc(sizeof(long) * 3);
	if (!*colour)
		return (ft_err_str(ERR_MSG_MALLOC), -1);
	i = 0;
	while (col_range[i])
	{
		if (!ft_is_number(col_range[i]))
			return (ft_err_2str(ERR_MSG_RANGE_COL, col_range[i]), \
			ft_destroy_tab(&col_range), -1);
		res = ft_atol(col_range[i]);
		if (res < 0 || res > 255)
		{
			ft_err_2str(ERR_MSG_RANGE_COL, col_range[i]);
			return (ft_destroy_tab(&col_range), -1);
		}
		(*colour)[i] = res;
		i++;
	}
	ft_destroy_tab(&col_range);
	return (0);
}

int	ft_is_colours(t_cub *cub, char *line)
{
	int		i;
	char	**col_range;

	if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "F\t", 2) && \
	ft_strncmp(line, "C ", 2) && ft_strncmp(line, "C\t", 2))
		return (ft_err_2str(ERR_MSG_COL_ID, line), -1);
	i = 1;
	while (line[i] && (line[i] == 32 || line[i] == 9))
		i++;
	if (line[i] && !(line[i] >= '0' && line[i] <= '9'))
		return (ft_err_2str(ERR_MSG_INVALID_COL, line), -1);
	if (ft_n_mot(&line[i], "\t ,\n") != 3)
		return (ft_err_2str(ERR_MSG_INVALID_COL, line), -1);
	if (ft_split(&col_range, &line[i], "\t ,\n") == EXIT_FAILURE)
		return (ft_err_str(ERR_MSG_MALLOC), -1);
	cub->parse->n_col++;
	if (line[0] == 'F')
		return (ft_get_colours(&cub->floor_colour, col_range));
	else if (line[0] == 'C')
		return (ft_get_colours(&cub->ceiling_colour, col_range));
	return (-1);
}
