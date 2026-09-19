/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:19:44 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/16 20:58:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_draw_frame_horizontal(t_cub *cub, int x_start,
	int x_end, int y)
{
	while (x_start < x_end)
	{
		cb_pixel_put_minimap(cub, x_start, y, cub->frame_color);
		x_start++;
	}
}

static void	st_draw_frame_vertical(t_cub *cub, int y_start,
	int y_end, int x)
{
	while (y_start < y_end)
	{
		cb_pixel_put_minimap(cub, x, y_start, cub->frame_color);
		y_start++;
	}
}

void	cb_draw_minimap_frame(t_cub *cub, int offset_x,
	int offset_y, int size)
{
	cub->frame_color = 0xFFFFFF;
	st_draw_frame_horizontal(cub, offset_x, offset_x + size,
		offset_y);
	st_draw_frame_horizontal(cub, offset_x, offset_x + size,
		offset_y + size - 1);
	st_draw_frame_vertical(cub, offset_y, offset_y + size,
		offset_x);
	st_draw_frame_vertical(cub, offset_y, offset_y + size,
		offset_x + size - 1);
}
