/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 08:17:46 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/25 11:06:32 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_line(char *s)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] && s[len] == '\n')
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

static void	new_stat(char *stat, t_gnl gnl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	if (stat[i])
	{
		while (i < gnl.len)
		{
			stat[j] = stat[i];
			j++;
			i++;
		}
	}
	stat[j] = '\0';
}

static char	*ft_read(char *stat, t_gnl gnl, int fd)
{
	gnl.stock_line = NULL;
	gnl.value = 1;
	if (stat[0] >= 0 && stat[0] <= 126)
	{
		gnl.stock_line = copy(stat);
		if (gnl.stock_line == NULL)
			return (NULL);
	}
	while (ft_check(stat) != 1 && gnl.value != 0)
	{
		gnl.value = read(fd, stat, BUFFER_SIZE);
		if (gnl.value == -1)
			return (free(gnl.stock_line), NULL);
		stat[gnl.value] = '\0';
		if (!gnl.stock_line)
			gnl.stock_line = copy(stat);
		else
			gnl.stock_line = join(gnl.stock_line, stat, gnl);
		if (!gnl.stock_line)
			return (NULL);
	}
	gnl.new_line = get_line(gnl.stock_line);
	gnl.len = ft_len(stat);
	new_stat(stat, gnl);
	return (free(gnl.stock_line), gnl.new_line);
}

char	*gnl(int fd)
{
	t_gnl		gnl;
	static char	stat[BUFFER_SIZE + 1];

	gnl.line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.line = ft_read(stat, gnl, fd);
	if (!gnl.line)
		return (NULL);
	return (gnl.line);
}
