/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:03 by gmarquis          #+#    #+#             */
/*   Updated: 2023/11/25 17:21:59 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_le_xav(char **str, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return ;
}

char	*ft_strlmemcpy(char *s, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

unsigned int	ft_countwords(char const *s, char c)
{
	unsigned int	i;
	unsigned int	trigger;
	unsigned int	count;

	i = 0;
	trigger = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			trigger = 1;
		else if (trigger == 1)
		{
			count++;
			trigger = 0;
		}
		i++;
	}
	return (count);
}

size_t	ft_wordlen(char *s, char c)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	counttab;
	char			**str;
	char			*strtemp;

	i = 0;
	if (!s)
		return (NULL);
	counttab = ft_countwords(s, c);
	strtemp = (char *)s;
	str = (char **)malloc((counttab + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (i < counttab && strtemp[0] != '\0')
	{
		while (*strtemp == c)
			strtemp++;
		str[i] = ft_strlmemcpy(strtemp, ft_wordlen(strtemp, c));
		if (!str[i])
			return (ft_le_xav(str, i), NULL);
		while (*strtemp != c && *strtemp)
			strtemp++;
		i++;
	}
	return (str[i] = NULL, str);
}
