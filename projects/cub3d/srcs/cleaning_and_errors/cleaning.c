/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:35 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/13 19:04:28 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_destroy_tab(char ***output)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*output == NULL)
		return ;
	while ((*output)[i])
	{
		tmp = (*output)[i];
		(*output)[i] = NULL;
		free(tmp);
		i++;
	}
	free(*output);
	*output = NULL;
}

void	*ft_free_tab(void *to_be_free)
{
	if (to_be_free == NULL)
		return (NULL);
	free(to_be_free);
	return (NULL);
}

void	ft_free_mlx(t_cub *cub)
{
	if (!cub->mlx_ptr)
		return ;
	if (cub->north_text)
		mlx_destroy_image(cub->mlx_ptr, cub->north_text);
	if (cub->south_text)
		mlx_destroy_image(cub->mlx_ptr, cub->south_text);
	if (cub->east_text)
		mlx_destroy_image(cub->mlx_ptr, cub->east_text);
	if (cub->west_text)
		mlx_destroy_image(cub->mlx_ptr, cub->west_text);
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	cub->mlx_ptr = NULL;
}

/*void	ft_free_mlx(t_cub *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->north_text);
	mlx_destroy_image(cub->mlx_ptr, cub->south_text);
	mlx_destroy_image(cub->mlx_ptr, cub->east_text);
	mlx_destroy_image(cub->mlx_ptr, cub->west_text);
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
}*/

void	free_parse_struct(t_cub *cub)
{
	cub->parse->north_text_path = ft_free_tab(cub->parse->north_text_path);
	cub->parse->south_text_path = ft_free_tab(cub->parse->south_text_path);
	cub->parse->east_text_path = ft_free_tab(cub->parse->east_text_path);
	cub->parse->west_text_path = ft_free_tab(cub->parse->west_text_path);
	free(cub->parse);
	cub->parse = NULL;
}

int	free_all(t_cub *cub)
{
	ft_free_mlx(cub);
	if (cub->parse != NULL)
		free_parse_struct(cub);
	cub->ceiling_colour = ft_free_tab(cub->ceiling_colour);
	cub->floor_colour = ft_free_tab(cub->floor_colour);
	cub->win_height = ft_free_tab(cub->win_height);
	cub->win_width = ft_free_tab(cub->win_width);
	ft_destroy_tab(&cub->map);
	exit (0);
}
