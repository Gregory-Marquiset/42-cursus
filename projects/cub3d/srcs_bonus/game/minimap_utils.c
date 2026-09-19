/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:27:27 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/16 21:20:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cb_pixel_put_minimap(t_cub *cub, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= *cub->win_width || y < 0 || y >= *cub->win_height)
		return ;
	dst = cub->addr + (y * cub->line_len) + (x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

static bool	st_is_point_in_triangle(double px, double py, t_triangle *triangle)
{
	bool	has_neg;
	bool	has_pos;

	double (d1) = (px - triangle->bx) * (triangle->ay - triangle->by)
		- (py - triangle->by) * (triangle->ax - triangle->bx);
	double (d2) = (px - triangle->cx) * (triangle->by - triangle->cy)
		- (py - triangle->cy) * (triangle->bx - triangle->cx);
	double (d3) = (px - triangle->ax) * (triangle->cy - triangle->ay)
		- (py - triangle->ay) * (triangle->cx - triangle->ax);
	has_neg = ((d1 < 0) || (d2 < 0) || (d3 < 0));
	has_pos = ((d1 > 0) || (d2 > 0) || (d3 > 0));
	return (!(has_neg && has_pos));
}

void	cb_fill_triangle_pixels(t_cub *cub, t_triangle *triangle)
{
	int	x;
	int	y;

	y = triangle->miny;
	while (y <= triangle->maxy)
	{
		x = triangle->minx;
		while (x <= triangle->maxx)
		{
			if (st_is_point_in_triangle(x + 0.5, y + 0.5, triangle))
				cb_pixel_put_minimap(cub, x, y, triangle->color);
			x++;
		}
		y++;
	}
}
