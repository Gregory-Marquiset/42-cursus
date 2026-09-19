/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:14:13 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 01:15:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	cb_perform_dda(t_cub *cub, t_dda *d)
{
	while (true)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (cub->map[d->mapy][d->mapx] == '1'
			|| cub->map[d->mapy][d->mapx] == 'C')
			break ;
	}
	return (d->side);
}

void	cb_init_dda(t_dda *d, t_cub *cub, t_ray *r)
{
	d->mapx = (int)cub->player.posx;
	d->mapy = (int)cub->player.posy;
	d->deltadistx = fabs(1.0 / r->raydirx);
	d->deltadisty = fabs(1.0 / r->raydiry);
	d->stepx = 1;
	d->sidedistx = ((int)cub->player.posx + 1.0 - cub->player.posx)
		* d->deltadistx;
	d->stepy = 1;
	d->sidedisty = ((int)cub->player.posy + 1.0 - cub->player.posy)
		* d->deltadisty;
	if (r->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (cub->player.posx - (int)cub->player.posx)
			* d->deltadistx;
	}
	if (r->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (cub->player.posy - (int)cub->player.posy)
			* d->deltadisty;
	}
}

void	cb_compute_line_dimensions(t_cub *cub, t_ray *r, t_dda *d)
{
	if (d->side == 0)
		r->perpwalldist = d->sidedistx - d->deltadistx;
	else
		r->perpwalldist = d->sidedisty - d->deltadisty;
	r->lineheight = (int)((double)*cub->win_height / r->perpwalldist);
	r->drawstart = -r->lineheight / 2 + *cub->win_height / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + *cub->win_height / 2;
	if (r->drawend >= *cub->win_height)
		r->drawend = *cub->win_height - 1;
}

void	cb_draw_floor_ceiling(t_cub *cub, int x, int start, int end)
{
	unsigned int (floorColor) = ((cub->floor_colour[0] & 0xFF) << 16)
		| ((cub->floor_colour[1] & 0xFF) << 8) | (cub->floor_colour[2] & 0xFF);
	unsigned int (ceilingColor) = ((cub->ceiling_colour[0] & 0xFF) << 16)
		| ((cub->ceiling_colour[1] & 0xFF) << 8)
		| (cub->ceiling_colour[2] & 0xFF);
	int (y) = 0;
	char *(pixel);
	while (y < start)
	{
		pixel = cub->addr
			+ (y * cub->line_len)
			+ (x * (cub->bpp / 8));
		*(unsigned int *)pixel = ceilingColor;
		y++;
	}
	y = end + 1;
	while (y < *cub->win_height)
	{
		pixel = cub->addr
			+ (y * cub->line_len)
			+ (x * (cub->bpp / 8));
		*(unsigned int *)pixel = floorColor;
		y++;
	}
}

t_img	*cb_select_texture(t_cub *cub, t_dda *d, t_ray *r)
{
	char (tile) = cub->map[d->mapy][d->mapx];
	if (tile == 'C')
		return (&cub->tex_door);
	if (d->side == 0)
	{
		if (r->raydirx > 0)
			return (&cub->tex_east);
		else
			return (&cub->tex_west);
	}
	else
	{
		if (r->raydiry > 0)
			return (&cub->tex_south);
		else
			return (&cub->tex_north);
	}
}
