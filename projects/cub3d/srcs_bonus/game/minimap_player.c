/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:20:00 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 01:27:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_calculate_bounding_box(t_triangle *triangle)
{
	triangle->minx = (int)floor(fmin(triangle->ax,
				fmin(triangle->bx, triangle->cx)));
	triangle->maxx = (int)ceil(fmax(triangle->ax,
				fmax(triangle->bx, triangle->cx)));
	triangle->miny = (int)floor(fmin(triangle->ay,
				fmin(triangle->by, triangle->cy)));
	triangle->maxy = (int)ceil(fmax(triangle->ay,
				fmax(triangle->by, triangle->cy)));
}

static void	st_calculate_triangle_vertices(double dirx, double diry,
	t_triangle *triangle)
{
	double	length;
	double	half_width;
	double	px;
	double	py;

	length = 10.0;
	half_width = 4.0;
	px = -diry;
	py = dirx;
	triangle->ax = triangle->center_x + dirx * length;
	triangle->ay = triangle->center_y + diry * length;
	triangle->bx = triangle->center_x + px * half_width;
	triangle->by = triangle->center_y + py * half_width;
	triangle->cx = triangle->center_x - px * half_width;
	triangle->cy = triangle->center_y - py * half_width;
}

static void	st_fill_triangle(t_cub *cub, t_triangle *triangle)
{
	triangle->minx = 0;
	triangle->maxx = 0;
	triangle->miny = 0;
	triangle->maxy = 0;
	st_calculate_triangle_vertices(cub->player.dirx, cub->player.diry,
		triangle);
	st_calculate_bounding_box(triangle);
	cb_fill_triangle_pixels(cub, triangle);
}

static void	st_normalize_vector(double *x, double *y)
{
	double	norm;

	norm = sqrt((*x) * (*x) + (*y) * (*y));
	if (norm > 0.0001)
	{
		*x /= norm;
		*y /= norm;
	}
}

void	cb_draw_player_on_minimap_fixed(t_cub *cub)
{
	t_triangle	triangle;
	int			margin;

	margin = 25;
	triangle.offset_x = margin;
	triangle.offset_y = margin;
	triangle.center_x = triangle.offset_x + 250 / 2;
	triangle.center_y = triangle.offset_y + 250 / 2;
	st_normalize_vector(&cub->player.dirx, &cub->player.diry);
	triangle.color = 0xFF0000;
	st_fill_triangle(cub, &triangle);
}
