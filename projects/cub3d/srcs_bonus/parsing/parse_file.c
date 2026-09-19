/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:33 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 01:30:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	st_check_filename(char *filename)
{
	int	i;

	if (!filename)
		return (0);
	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.' && i != 0)
		{
			if (ft_strcmp(&filename[i], ".cub") == 0 && \
			filename[i + 4] == '\0')
				return (1);
			break ;
		}
		i++;
	}
	ft_err_str(ERR_MSG_FILENAME);
	return (0);
}

static int	ft_check_line(t_cub *cub, char *file_line, int n)
{
	int (i) = 0;
	while (file_line[i] && ft_is_whitespace(file_line[i]))
		i++;
	if (file_line[i] && !ft_is_whitespace(file_line[i]))
	{
		if (ft_is_charset("NSEW", file_line[i]) && cub->parse->map_start == 0)
			return (ft_is_texture(cub->parse, &file_line[i]));
		else if (ft_is_charset("FC", file_line[i]) && \
			cub->parse->map_start == 0)
			return (ft_is_colours(cub, &file_line[i]));
		else if (file_line[i] == '1')
		{
			if (cub->parse->n_text != 4 || cub->parse->n_col != 2)
				return (ft_err_str(ERR_MSG_INV), -1);
			return (ft_is_mapline(cub, &file_line[0], n));
		}
		if (cub->parse->map_start > 0 && file_line[i] == '0')
			return (ft_err_2str(ERR_MSG_MAP_OP, file_line), -1);
		else if (cub->parse->map_start > 0 && \
		ft_is_charset("NSEW", file_line[i]) && \
		!ft_is_identifier(cub->parse, &file_line[i]))
			return (ft_err_str(ERR_MSG_PLAYER), -1);
		return (ft_err_2str(ERR_MSG_INVALID, file_line), -1);
	}
	return (cub->parse->door_text_path = "./textures/door.xpm", 0);
}

static int	ft_check_map_validity(t_cub *cub, char *file_line, int file_fd)
{
	int	n;

	n = 0;
	while (true)
	{
		file_line = gnl(file_fd);
		if (!file_line)
			return (free(file_line), ft_err_str(ERR_MSG_MALLOC), -1);
		if (file_line[0] == '\0')
			break ;
		if (ft_check_line(cub, file_line, n) == -1)
			return (free(file_line), -1);
		free(file_line);
		n++;
	}
	free(file_line);
	if (cub->parse->player == 0)
		return (ft_err_str(ERR_MSG_NO_PLAYER), -1);
	cub->parse->numb_of_line = cub->parse->last_map_line - \
	cub->parse->map_start + 1;
	return (0);
}

int	ft_parse_file(t_cub *cub, char *filename)
{
	int		file_fd;
	char	*file_line;

	file_line = NULL;
	if (!st_check_filename(filename))
		return (EXIT_FAILURE);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (perror(filename), EXIT_FAILURE);
	if (ft_check_map_validity(cub, file_line, file_fd) == -1)
		return (EXIT_FAILURE);
	close(file_fd);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (perror(filename), EXIT_FAILURE);
	if (ft_get_map(cub, file_fd) == -1)
		return (EXIT_FAILURE);
	if (ft_set_textures(cub) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
