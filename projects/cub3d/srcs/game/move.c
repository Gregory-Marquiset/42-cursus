/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:50:20 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 06:32:59 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cb_move_forward(t_cub *cub)
{
	double	move_speed;
	double	newx;
	double	newy;

	move_speed = 0.1;
	newx = cub->player.posx + cub->player.dirx * move_speed;
	newy = cub->player.posy + cub->player.diry * move_speed;
	cb_collision(cub, newx, newy);
}

void	cb_move_backward(t_cub *cub)
{
	double	move_speed;
	double	newx;
	double	newy;

	move_speed = 0.1;
	newx = cub->player.posx - cub->player.dirx * move_speed;
	newy = cub->player.posy - cub->player.diry * move_speed;
	cb_collision(cub, newx, newy);
}

void	cb_move_left(t_cub *cub)
{
	double	move_speed;
	double	newx;
	double	newy;
	double	perpx;
	double	perpy;

	move_speed = 0.1;
	perpx = cub->player.diry;
	perpy = -cub->player.dirx;
	newx = cub->player.posx + perpx * move_speed;
	newy = cub->player.posy + perpy * move_speed;
	cb_collision(cub, newx, newy);
}

void	cb_move_right(t_cub *cub)
{
	double	move_speed;
	double	newx;
	double	newy;
	double	perpx;
	double	perpy;

	move_speed = 0.1;
	perpx = -cub->player.diry;
	perpy = cub->player.dirx;
	newx = cub->player.posx + perpx * move_speed;
	newy = cub->player.posy + perpy * move_speed;
	cb_collision(cub, newx, newy);
}
