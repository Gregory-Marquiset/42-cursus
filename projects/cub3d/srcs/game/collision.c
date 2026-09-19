/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:03:27 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 01:15:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	st_get_map_width(char **map)
{
	int	width;
	int	row;
	int	len;

	width = 0;
	row = 0;
	while (map[row])
	{
		len = 0;
		while (map[row][len])
			len++;
		if (len > width)
			width = len;
		row++;
	}
	return (width);
}

static int	st_get_map_height(char **map)
{
	int	row;

	row = 0;
	while (map[row])
		row++;
	return (row);
}

static bool	st_is_valid_cell(t_cub *cub, double x, double y)
{
	int	mapw;
	int	maph;
	int	col;
	int	row;

	mapw = st_get_map_width(cub->map);
	maph = st_get_map_height(cub->map);
	col = (int)x;
	row = (int)y;
	if (col < 0 || col >= mapw || row < 0 || row >= maph)
		return (false);
	if (cub->map[row][col] == '1' || cub->map[row][col] == 'C')
		return (false);
	return (true);
}

static bool	st_is_valid_position(t_cub *cub, double newx, double newy)
{
	double	margin;

	margin = 0.1;
	if (!st_is_valid_cell(cub, newx - margin, newy - margin))
		return (false);
	if (!st_is_valid_cell(cub, newx + margin, newy - margin))
		return (false);
	if (!st_is_valid_cell(cub, newx - margin, newy + margin))
		return (false);
	if (!st_is_valid_cell(cub, newx + margin, newy + margin))
		return (false);
	return (true);
}

void	cb_collision(t_cub *cub, double newx, double newy)
{
	if (!st_is_valid_position(cub, newx, newy))
		return ;
	cub->player.posx = newx;
	cub->player.posy = newy;
}
