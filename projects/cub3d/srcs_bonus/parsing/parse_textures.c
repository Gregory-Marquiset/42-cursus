/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:33:25 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 04:19:26 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	st_load_coin_frames(t_cub *cub)
{
	char *(frame_paths)[8] = {
		"textures/coin/frame_0_delay-0.1s.xpm",
		"textures/coin/frame_1_delay-0.1s.xpm",
		"textures/coin/frame_2_delay-0.1s.xpm",
		"textures/coin/frame_3_delay-0.1s.xpm",
		"textures/coin/frame_4_delay-0.1s.xpm",
		"textures/coin/frame_5_delay-0.1s.xpm",
		"textures/coin/frame_6_delay-0.1s.xpm",
		"textures/coin/frame_7_delay-0.1s.xpm"
	};
	int (i) = 0;
	while (i < 8)
	{
		cub->coin_frames[i].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
				frame_paths[i], &cub->coin_frames[i].width,
				&cub->coin_frames[i].height);
		if (!cub->coin_frames[i].img_ptr)
			ft_err_str("Error loading coin frame.");
		cub->coin_frames[i].addr = mlx_get_data_addr(
				cub->coin_frames[i].img_ptr, &cub->coin_frames[i].bpp,
				&cub->coin_frames[i].line_len, &cub->coin_frames[i].endian);
		i++;
	}
	cub->current_coin_frame = 0;
	cub->last_coin_update = 0;
}

static void	init_tex(t_img *tex, void *img_ptr, int width, int height)
{
	int	bpp;
	int	line_len;
	int	endian;

	tex->img_ptr = img_ptr;
	tex->width = width;
	tex->height = height;
	tex->addr = mlx_get_data_addr(img_ptr, &bpp, &line_len, &endian);
	tex->bpp = bpp;
	tex->line_len = line_len;
	tex->endian = endian;
}

static void	st_set_tex_helper(t_cub *cub, int width, int height)
{
	init_tex(&cub->tex_north, cub->north_text, width, height);
	init_tex(&cub->tex_south, cub->south_text, width, height);
	init_tex(&cub->tex_east, cub->east_text, width, height);
	init_tex(&cub->tex_west, cub->west_text, width, height);
	init_tex(&cub->tex_door, cub->door_text, width, height);
	st_load_coin_frames(cub);
}

int	ft_set_textures(t_cub *cub)
{
	int (width) = PXL;
	int (height) = PXL;
	cub->north_text = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->parse->north_text_path, &width, &height);
	if (!cub->north_text)
		return (ft_err_str(ERR_MSG_LOAD_TEXT), -1);
	cub->south_text = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->parse->south_text_path, &width, &height);
	if (!cub->south_text)
		return (ft_err_str(ERR_MSG_LOAD_TEXT), -1);
	cub->east_text = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->parse->east_text_path, &width, &height);
	if (!cub->east_text)
		return (ft_err_str(ERR_MSG_LOAD_TEXT), -1);
	cub->west_text = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->parse->west_text_path, &width, &height);
	if (!cub->west_text)
		return (ft_err_str(ERR_MSG_LOAD_TEXT), -1);
	cub->door_text = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->parse->door_text_path, &width, &height);
	if (!cub->door_text)
		return (ft_err_str(ERR_MSG_LOAD_TEXT), -1);
	return (st_set_tex_helper(cub, width, height), 0);
}
