/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 14:23:59 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	phb_speaking(t_sympos *sympos, int philo_id, char *msg)
{
	unsigned long	t;

	sem_wait(sympos->sem_one_death);
	sem_wait(sympos->sem_log);
	t = phb_actualtime() - sympos->philos[0].agal->st_time;
	printf("%lu %d %s", t, philo_id, msg);
	sem_post(sympos->sem_log);
	sem_post(sympos->sem_one_death);
}

void	phb_speaking_for_dead(t_sympos *sympos, int philo_id)
{
	unsigned long	t;

	sem_wait(sympos->sem_one_death);
	sem_wait(sympos->sem_log);
	t = phb_actualtime() - sympos->philos[0].agal->st_time;
	printf("%lu %d died\n", t, philo_id);
	sem_post(sympos->sem_log);
}

unsigned long	phb_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf(LERR_GETTIME);
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

void	phb_waiting(unsigned long time)
{
	unsigned long	init_time;

	init_time = phb_actualtime();
	while ((phb_actualtime() - init_time) < time)
	{
		usleep(time / 100);
	}
}
