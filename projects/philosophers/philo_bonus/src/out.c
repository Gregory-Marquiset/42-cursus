/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 12:48:51 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static unsigned long	st_strlen(char *str)
{
	unsigned long (i) = 0;
	while (str[i])
		i++;
	return (i);
}

static void	st_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, st_strlen(message));
	exit(error_code);
}

static void	phb_sem_close(t_sympos *sympos)
{
	if (sympos->sem_forks != SEM_FAILED && sympos->sem_forks != NULL)
	{
		sem_close(sympos->sem_forks);
		sem_unlink("sem_forks");
	}
	if (sympos->sem_log != SEM_FAILED && sympos->sem_log != NULL)
	{
		sem_close(sympos->sem_log);
		sem_unlink("sem_log");
	}
	if (sympos->sem_one_death && sympos->sem_one_death != SEM_FAILED)
	{
		sem_close(sympos->sem_one_death);
		sem_unlink("sem_one_death");
	}
}

void	phb_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int (i) = 0;
	if (sympos)
	{
		if (sympos->philos)
		{
			while (i < sympos->n_philos)
			{
				free(sympos->philos[i].agal);
				i++;
			}
			free(sympos->philos);
		}
		phb_sem_close(sympos);
		free(sympos);
	}
	st_exit(fd_out, message, error_code);
}
