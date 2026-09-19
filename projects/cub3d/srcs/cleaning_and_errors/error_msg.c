/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:15:24 by cdutel            #+#    #+#             */
/*   Updated: 2024/11/13 16:47:04 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_err_str(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
}

void	ft_err_2str(char *err_msg1, char *err_msg2)
{
	write(2, err_msg1, ft_strlen(err_msg1));
	write(2, err_msg2, ft_strlen(err_msg2));
	write(2, "\n", 2);
}
