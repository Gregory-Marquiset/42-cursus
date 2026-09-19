/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:39:46 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:55:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_cub(t_cub *cub)
{
	t_parse	*parsing;

	cub->win_width = malloc(sizeof(int));
	if (!cub->win_width)
		return (ft_err_str(ERR_MSG_MALLOC), EXIT_FAILURE);
	cub->win_height = malloc(sizeof(int));
	if (!cub->win_height)
		return (ft_err_str(ERR_MSG_MALLOC), EXIT_FAILURE);
	parsing = calloc(1, sizeof(t_parse));
	if (!parsing)
		return (ft_err_str(ERR_MSG_MALLOC), EXIT_FAILURE);
	cub->parse = parsing;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_err_str(ERR_MSG_ARG), EXIT_FAILURE);
	ft_bzero(&cub, sizeof(t_cub));
	if (init_cub(&cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		return (free_all(&cub), EXIT_FAILURE);
	if (ft_parse_file(&cub, argv[1]) == EXIT_FAILURE)
		return (free_all(&cub), EXIT_FAILURE);
	cb_set_and_display_game(&cub);
	return (0);
}
