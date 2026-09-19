/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:11:12 by gmarquis          #+#    #+#             */
/*   Updated: 2023/11/21 14:11:13 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	chara;

	i = 0;
	chara = c;
	while (s[i])
		i++;
	while (s[i] >= 0)
	{
		if (s[i] == chara)
			return ((char *)s + i);
		if (i == 0 && s[i] != chara)
			return (0);
		i--;
	}
	return (0);
}
