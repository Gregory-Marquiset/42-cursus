/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:11:07 by gmarquis          #+#    #+#             */
/*   Updated: 2023/11/23 14:38:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	index;

	index = 0;
	if (!big && !len)
		return (0);
	if (!*little)
		return ((char *)big);
	while (big[index] && index < len)
	{
		if (big[index] == little[0])
		{
			i = 1;
			while (little[i] && little[i] == big[i + index] && (index
					+ i) < len)
				i++;
			if (little[i] == '\0')
				return ((char *)&big[index]);
		}
		index++;
	}
	return (0);
}
