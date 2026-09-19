/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:20:58 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/05 12:11:05 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	long unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n == 1)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int main()
{
	__builtin_printf("%d\n", strncmp("", "", 1));
	__builtin_printf("%d\n", ft_strncmp("", "", 1));
	return 0;
}*/
