/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_speaking(t_epis *epis, int id, char *message)
{
	unsigned long	st_time;
	int				verif;

	st_time = *epis->st_time;
	pthread_mutex_lock(&epis->mtx_verif);
	verif = *(epis->verif);
	pthread_mutex_unlock(&epis->mtx_verif);
	if (verif == -2)
		return (1);
	pthread_mutex_lock(&epis->mtx_printf);
	printf("%ld %d %s", (ph_actualtime() - st_time), id, message);
	pthread_mutex_unlock(&epis->mtx_printf);
	return (0);
}

void	ph_waiting(unsigned long time, pthread_mutex_t *mutex, int *var)
{
	unsigned long	start_time;
	unsigned long	elapsed;

	start_time = ph_actualtime();
	elapsed = 0;
	while (elapsed < time)
	{
		usleep(1000);
		elapsed = ph_actualtime() - start_time;
		if (ph_take_var(mutex, var) != 0)
			break ;
	}
}
