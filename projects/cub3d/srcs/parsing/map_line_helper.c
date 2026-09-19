/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:46 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:52:25 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_complete_map(t_cub *cub, int i, int *index)
{
	while (i < cub->parse->len_max + 1)
	{
		(cub)->map[*index][i] = '9';
		i++;
	}
}

void	ft_set_player_dir(t_cub *cub, char direction)
{
	cub->player.dirx = 0.0;
	cub->player.diry = -1.0;
	cub->player.planex = 0.66;
	cub->player.planey = 0.0;
	if (direction == 'S')
	{
		cub->player.diry = 1.0;
		cub->player.planex = -0.66;
	}
	else if (direction == 'E')
	{
		cub->player.dirx = 1.0;
		cub->player.diry = 0.0;
		cub->player.planex = 0.0;
		cub->player.planey = 0.66;
	}
	else if (direction == 'W')
	{
		cub->player.dirx = -1.0;
		cub->player.diry = 0.0;
		cub->player.planex = 0.0;
		cub->player.planey = -0.66;
	}
}

void	ft_set_player_position(t_cub *cub, int i, int index, char direction)
{
	cub->player.posx = i + 0.5;
	cub->player.posy = index + 0.5;
	ft_set_player_dir(cub, direction);
	cub->map[index][i] = '0';
	cub->parse->player++;
}

void	ft_handle_tab(t_cub *cub, int *i, int index)
{
	int	k;

	k = 0;
	while (k < 4 && *i + k < cub->parse->len_max)
	{
		cub->map[index][*i + k] = '9';
		k++;
	}
	*i += (k - 1);
}

void	ft_fill_map_char(t_cub *cub, char c, int i, int index)
{
	if (c == ' ' || c == '\n')
		cub->map[index][i] = '9';
	else
		cub->map[index][i] = c;
}
