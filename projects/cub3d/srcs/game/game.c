/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:50:20 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 06:00:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_rotate_left(t_cub *cub)
{
	double	rot_speed;
	double	old_dirx;
	double	old_planex;

	rot_speed = -0.05;
	old_dirx = cub->player.dirx;
	old_planex = cub->player.planex;
	cub->player.dirx = cub->player.dirx * cos(rot_speed)
		- cub->player.diry * sin(rot_speed);
	cub->player.diry = old_dirx * sin(rot_speed)
		+ cub->player.diry * cos(rot_speed);
	cub->player.planex = cub->player.planex * cos(rot_speed)
		- cub->player.planey * sin(rot_speed);
	cub->player.planey = old_planex * sin(rot_speed)
		+ cub->player.planey * cos(rot_speed);
}

static void	st_rotate_right(t_cub *cub)
{
	double	rot_speed;
	double	old_dirx;
	double	old_planex;

	rot_speed = 0.05;
	old_dirx = cub->player.dirx;
	old_planex = cub->player.planex;
	cub->player.dirx = cub->player.dirx * cos(rot_speed)
		- cub->player.diry * sin(rot_speed);
	cub->player.diry = old_dirx * sin(rot_speed)
		+ cub->player.diry * cos(rot_speed);
	cub->player.planex = cub->player.planex * cos(rot_speed)
		- cub->player.planey * sin(rot_speed);
	cub->player.planey = old_planex * sin(rot_speed)
		+ cub->player.planey * cos(rot_speed);
}

static int	st_key_press(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		free_all(cub);
	else if (keycode == 119)
		cb_move_forward(cub);
	else if (keycode == 115)
		cb_move_backward(cub);
	else if (keycode == 97)
		cb_move_left(cub);
	else if (keycode == 100)
		cb_move_right(cub);
	else if (keycode == 65361)
		st_rotate_left(cub);
	else if (keycode == 65363)
		st_rotate_right(cub);
	return (0);
}

int	cb_set_and_display_game(t_cub *cub)
{
	mlx_get_screen_size(cub->mlx_ptr, cub->win_width, cub->win_height);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, *cub->win_width,
			*cub->win_height, NAME);
	if (!cub->win_ptr)
		return (ft_err_str(ERR_MSG_WINDOW), -1);
	mlx_hook(cub->win_ptr, 17, 0L, &free_all, cub);
	mlx_hook(cub->win_ptr, 2, 1L << 0, &st_key_press, cub);
	mlx_loop_hook(cub->mlx_ptr, &cb_render_frame, cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}
