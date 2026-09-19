/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:36:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_take_var(pthread_mutex_t *mutex, int *var)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(mutex);
	tmp = *var;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

void	ph_incr_var(pthread_mutex_t *mutex, int *var)
{
	pthread_mutex_lock(mutex);
	*var += 1;
	pthread_mutex_unlock(mutex);
}

void	ph_modif_var(pthread_mutex_t *mutex, int *dest, int src)
{
	pthread_mutex_lock(mutex);
	*dest = src;
	pthread_mutex_unlock(mutex);
}

unsigned long	ph_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf(LERR_GETTIME);
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}
