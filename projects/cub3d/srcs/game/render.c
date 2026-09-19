/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:50:20 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 05:58:49 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_dtw_helper	st_init_dtw_helper(t_cub *cub, t_dda *d, t_ray *r)
{
	t_dtw_helper	dtw;

	dtw.y = 0;
	dtw.tex_x = 0;
	dtw.tex_y = 0;
	dtw.line_height = 0;
	dtw.draw_start = 0;
	dtw.draw_end = 0;
	dtw.color = 0;
	dtw.step = 0;
	dtw.tex_pos = 0;
	if (d->side == 0)
		dtw.wallx = cub->player.posy + r->perpwalldist * r->raydiry;
	else
		dtw.wallx = cub->player.posx + r->perpwalldist * r->raydirx;
	dtw.texel = 0;
	dtw.dst = 0;
	dtw.tex = cb_select_texture(cub, d, r);
	return (dtw);
}

static void	st_draw_textured_wall(t_cub *cub, t_dda *d, t_ray *r, int x)
{
	t_dtw_helper	dtw;

	dtw = st_init_dtw_helper(cub, d, r);
	dtw.wallx -= floor(dtw.wallx);
	dtw.tex_x = (int)(dtw.wallx * (double)dtw.tex->width);
	dtw.line_height = r->lineheight;
	dtw.draw_start = r->drawstart;
	dtw.draw_end = r->drawend;
	dtw.step = 1.0 * dtw.tex->height / dtw.line_height;
	dtw.tex_pos = (dtw.draw_start - *cub->win_height / 2.0
			+ dtw.line_height / 2.0) * dtw.step;
	dtw.y = dtw.draw_start;
	while (dtw.y < dtw.draw_end)
	{
		dtw.tex_y = (int)dtw.tex_pos & (dtw.tex->height - 1);
		dtw.tex_pos += dtw.step;
		dtw.texel = dtw.tex->addr + (dtw.tex_y * dtw.tex->line_len)
			+ (dtw.tex_x * (dtw.tex->bpp / 8));
		dtw.color = *(unsigned int *)dtw.texel;
		dtw.dst = cub->addr + (dtw.y * cub->line_len) + (x * (cub->bpp / 8));
		*(unsigned int *)dtw.dst = dtw.color;
		dtw.y++;
	}
}

static void	st_draw_walls(t_cub *cub)
{
	int		x;
	t_ray	r;
	t_dda	d;

	x = 0;
	while (x < *cub->win_width)
	{
		r.camerax = 2.0 * x / (double)*cub->win_width - 1.0;
		r.raydirx = cub->player.dirx + cub->player.planex * r.camerax;
		r.raydiry = cub->player.diry + cub->player.planey * r.camerax;
		cb_init_dda(&d, cub, &r);
		cb_perform_dda(cub, &d);
		cb_compute_line_dimensions(cub, &r, &d);
		cb_draw_floor_ceiling(cub, x, r.drawstart, r.drawend);
		st_draw_textured_wall(cub, &d, &r, x);
		x++;
	}
}

int	cb_render_frame(t_cub *cub)
{
	int *(col) = cub->floor_colour;
	int (r) = col[0];
	int (g) = col[1];
	int (b) = col[2];
	cub->floor = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
	col = cub->floor_colour;
	r = col[0];
	g = col[1];
	b = col[2];
	cub->ceil = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, *cub->win_width,
			*cub->win_height);
	if (!cub->img_ptr)
		return (free_all(cub), EXIT_FAILURE);
	cub->addr = mlx_get_data_addr(cub->img_ptr, &cub->bpp,
			&cub->line_len, &cub->endian);
	st_draw_walls(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->img_ptr);
	cub->img_ptr = NULL;
	return (0);
}
