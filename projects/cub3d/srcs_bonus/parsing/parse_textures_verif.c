/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_verif.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:42:28 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/17 00:17:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_is_identifier(t_parse *parse, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
	{
		parse->id = NO;
		return (1);
	}
	else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
	{
		parse->id = SO;
		return (1);
	}
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
	{
		parse->id = WE;
		return (1);
	}
	else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
	{
		parse->id = EA;
		return (1);
	}
	return (0);
}

static int	ft_check_textures_files(t_parse *parse)
{
	if (!ft_strcmp(parse->north_text_path, parse->south_text_path) || \
	!ft_strcmp(parse->north_text_path, parse->east_text_path) || \
	!ft_strcmp(parse->north_text_path, parse->west_text_path) || \
	!ft_strcmp(parse->south_text_path, parse->east_text_path) || \
	!ft_strcmp(parse->south_text_path, parse->west_text_path) || \
	!ft_strcmp(parse->east_text_path, parse->west_text_path))
		return (ft_err_str(ERR_MSG_TEXT_NAME), -1);
	if (open(parse->north_text_path, O_RDONLY) == -1)
		return (ft_err_2str(ERR_MSG_OPEN_TEXT, parse->north_text_path), -1);
	if (open(parse->south_text_path, O_RDONLY) == -1)
		return (ft_err_2str(ERR_MSG_OPEN_TEXT, parse->south_text_path), -1);
	if (open(parse->east_text_path, O_RDONLY) == -1)
		return (ft_err_2str(ERR_MSG_OPEN_TEXT, parse->east_text_path), -1);
	if (open(parse->west_text_path, O_RDONLY) == -1)
		return (ft_err_2str(ERR_MSG_OPEN_TEXT, parse->west_text_path), -1);
	if (open(parse->door_text_path, O_RDONLY) == -1)
		return (ft_err_2str(ERR_MSG_OPEN_TEXT, parse->door_text_path), -1);
	return (0);
}

static int	ft_dup_texture(t_parse *parse, char *line, int len)
{
	if (parse->id == NO)
	{
		if (parse->north_text_path)
			return (ft_err_str(ERR_MSG_2_NORTH_TEXT), 1);
		return (ft_strndup(&parse->north_text_path, line, len));
	}
	else if (parse->id == SO)
	{
		if (parse->south_text_path != NULL)
			return (ft_err_str(ERR_MSG_2_SOUTH_TEXT), 1);
		return (ft_strndup(&parse->south_text_path, line, len));
	}
	else if (parse->id == EA)
	{
		if (parse->east_text_path != NULL)
			return (ft_err_str(ERR_MSG_2_EAST_TEXT), 1);
		return (ft_strndup(&parse->east_text_path, line, len));
	}
	else if (parse->id == WE)
	{
		if (parse->west_text_path != NULL)
			return (ft_err_str(ERR_MSG_2_WEST_TEXT), 1);
		return (ft_strndup(&parse->west_text_path, line, len));
	}
	return (0);
}

int	ft_is_texture(t_parse *parse, char *line)
{
	int	i;
	int	len;
	int	path_start;

	if (!ft_is_identifier(parse, line))
		return (ft_err_2str(ERR_MSG_TEXT_ID, line), -1);
	i = 2;
	while (line[i] && (line[i] == 32 || line[i] == 9))
		i++;
	path_start = i;
	while (line[i] && !ft_is_whitespace(line[i]))
		i++;
	len = ft_strlen(line);
	while (ft_is_whitespace(line[len - 1]))
		len--;
	if (i != len)
		return (ft_err_2str(ERR_MSG_INVALID_TEXT, line), -1);
	if (ft_dup_texture(parse, &line[path_start], len - path_start) == 1)
		return (-1);
	parse->n_text++;
	if (parse->n_text == 5)
		return (ft_check_textures_files(parse));
	return (0);
}
