/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:20:17 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 01:27:54 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_fill_minimap_background(t_cub *cub, int offset_x,
	int offset_y, int size)
{
	int	y;
	int	x;

	y = offset_y;
	while (y < offset_y + size)
	{
		x = offset_x;
		while (x < offset_x + size)
		{
			cb_pixel_put_minimap(cub, x, y, 0x444444);
			x++;
		}
		y++;
	}
}

static unsigned int	st_get_cell_color(char cell)
{
	if (cell == '1')
		return (0x222222);
	else if (cell == '9')
		return (0x444444);
	else if (cell == 'C')
		return (0x666666);
	else if (cell == 'O')
		return (0xFFFFFF);
	return (0x999999);
}

static void	st_draw_map_cell(t_cub *cub, int col, int row)
{
	double (dx) = col - cub->player.posx;
	double (dy) = row - cub->player.posy;
	int (mini_x) = cub->center_x + (int)(dx * 8);
	int (mini_y) = cub->center_y + (int)(dy * 8);
	int (py) = 0;
	int (px) = 0;
	int (xx) = mini_x + px;
	int (yy) = mini_y + py;
	while (py < 8)
	{
		px = 0;
		while (px < 8)
		{
			xx = mini_x + px;
			yy = mini_y + py;
			if (xx >= cub->center_x - 250 / 2 && xx < cub->center_x
				+ 250 / 2 && yy >= cub->center_y - 250
				/ 2 && yy < cub->center_y + 250 / 2)
				cb_pixel_put_minimap(cub, xx, yy,
					st_get_cell_color(cub->map[row][col]));
			px++;
		}
		py++;
	}
}

static void	st_draw_map_cells(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	while (cub->map[row])
	{
		col = 0;
		while (cub->map[row][col])
		{
			st_draw_map_cell(cub, col, row);
			col++;
		}
		row++;
	}
}

void	cb_draw_minimap_fixed(t_cub *cub)
{
	int	offset_x;
	int	offset_y;
	int	margin;

	margin = 25;
	offset_x = margin;
	offset_y = margin;
	cub->center_x = offset_x + 250 / 2;
	cub->center_y = offset_y + 250 / 2;
	st_fill_minimap_background(cub, offset_x, offset_y, 250);
	st_draw_map_cells(cub);
	cb_draw_minimap_frame(cub, offset_x, offset_y, 250);
}
