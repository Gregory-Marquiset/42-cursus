/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:12:20 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/16 21:27:23 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	recenter_mouse(int *center_x, int *center_y, t_cub *cub)
{
	*center_x = *cub->win_width / 2;
	*center_y = *cub->win_height / 2;
	mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, *center_x, *center_y);
}

static void	rotate_player(double rot_speed, t_cub *cub)
{
	double (old_dirx) = cub->player.dirx;
	double (old_planex) = cub->player.planex;
	cub->player.dirx = cub->player.dirx * cos(rot_speed)
		- cub->player.diry * sin(rot_speed);
	cub->player.diry = old_dirx * sin(rot_speed)
		+ cub->player.diry * cos(rot_speed);
	cub->player.planex = cub->player.planex * cos(rot_speed)
		- cub->player.planey * sin(rot_speed);
	cub->player.planey = old_planex * sin(rot_speed)
		+ cub->player.planey * cos(rot_speed);
}

int	cb_mouse_move(int x, int y, t_cub *cub)
{
	static int (is_recentering) = 0;
	static int (center_x) = -1;
	static int (center_y) = -1;
	double (rot_speed);
	(void)y;
	if (center_x == -1 || center_y == -1)
	{
		recenter_mouse(&center_x, &center_y, cub);
		return (0);
	}
	if (is_recentering)
	{
		is_recentering = 0;
		return (0);
	}
	rot_speed = 0.0025 * (x - center_x);
	if (rot_speed != 0)
		rotate_player(rot_speed, cub);
	is_recentering = 1;
	mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, center_x, center_y);
	return (0);
}
