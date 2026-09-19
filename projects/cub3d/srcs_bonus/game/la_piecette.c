/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   la_piecette.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 04:16:22 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 04:25:51 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_draw_coin(t_cub *cub)
{
	t_img *(current_frame) = &cub->coin_frames[cub->current_coin_frame];
	int (offset_x) = 300;
	int (offset_y) = 25;
	int (x) = 0;
	int (y) = 0;
	unsigned int (color);
	char *(src_pixel);
	while (x < current_frame->width)
	{
		y = 0;
		while (y < current_frame->height)
		{
			src_pixel = current_frame->addr
				+ (y * current_frame->line_len)
				+ (x * (current_frame->bpp / 8));
			color = *(unsigned int *)src_pixel;
			if ((color & 0xFF000000) != 0xFF000000)
				cb_pixel_put_minimap(cub, offset_x + x, offset_y + y, color);
			y++;
		}
		x++;
	}
}

static unsigned long	cb_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		perror("error: echec gettimeofday\n");
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

void	cb_update_coin_frame(t_cub *cub)
{
	double (current_time) = cb_actualtime();
	if (current_time - cub->last_coin_update >= 100)
	{
		cub->current_coin_frame = (cub->current_coin_frame + 1) % 8;
		cub->last_coin_update = current_time;
	}
	st_draw_coin(cub);
}
