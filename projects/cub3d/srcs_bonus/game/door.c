/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:36:29 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/16 22:36:46 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	toggle_door_at_position(t_cub *cub, int nx, int ny)
{
	if (nx >= 0 && ny >= 0 && cub->map[ny] && cub->map[ny][nx])
	{
		if (cub->map[ny][nx] == 'C' && (nx != (int)cub->player.posx
			|| ny != (int)cub->player.posy))
		{
			cub->map[ny][nx] = 'O';
			return (1);
		}
		else if (cub->map[ny][nx] == 'O' && (nx != (int)cub->player.posx
			|| ny != (int)cub->player.posy))
		{
			cub->map[ny][nx] = 'C';
			return (1);
		}
	}
	return (0);
}

void	cb_toggle_door(t_cub *cub)
{
	int	dx;
	int	dy;
	int	nx;
	int	ny;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			nx = (int)cub->player.posx + dx;
			ny = (int)cub->player.posy + dy;
			if (toggle_door_at_position(cub, nx, ny))
				return ;
			dy++;
		}
		dx++;
	}
}
