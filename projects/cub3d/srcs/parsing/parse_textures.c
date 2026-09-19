/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:33:25 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:55:25 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	return (st_set_tex_helper(cub, width, height), 0);
}
