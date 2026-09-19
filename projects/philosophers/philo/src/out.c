/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static unsigned long	ph_strlen(char *str)
{
	unsigned long (i) = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ph_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, ph_strlen(message));
	exit(error_code);
}

static void	*ph_free_epis(t_epis *epis)
{
	if (epis)
	{
		free(epis->id_dead);
		free (epis->verif);
		free(epis->phs_meals);
		free(epis->st_time);
		pthread_mutex_destroy(&epis->mtx_id_dead);
		pthread_mutex_destroy(&epis->mtx_phs_meals);
		pthread_mutex_destroy(&epis->mtx_printf);
		pthread_mutex_destroy(&epis->mtx_verif);
		free(epis);
	}
	return (NULL);
}

void	ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int (n_philos) = 0;
	int (i) = 0;
	if (sympos)
	{
		if (sympos->epis)
		{
			n_philos = sympos->epis->n_philos;
			sympos->epis = ph_free_epis(sympos->epis);
		}
		if (sympos->philos)
		{
			while (i < n_philos)
			{
				pthread_mutex_destroy(&sympos->philos[i].rg_fork);
				free(sympos->philos[i].kine->last_meal);
				free(sympos->philos[i].kine->count_meal);
				free(sympos->philos[i].kine);
				free(sympos->philos[i].agal);
				i++;
			}
			free(sympos->philos);
		}
		free(sympos);
	}
	ph_exit(fd_out, message, error_code);
}
