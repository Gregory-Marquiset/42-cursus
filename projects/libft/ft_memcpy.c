/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:06:59 by gmarquis          #+#    #+#             */
/*   Updated: 2023/11/23 16:41:04 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*str;
	char		*dst;

	if ((dest == src) || n == 0)
		return (dest);
	str = (const char *)src;
	dst = (char *)dest;
	while (n--)
		*dst++ = *str++;
	return (dest);
}
