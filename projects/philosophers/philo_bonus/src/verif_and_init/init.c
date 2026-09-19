/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 12:25:14 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static void	phb_init_semaphores(t_sympos *sympos)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_log");
	sem_unlink("sem_one_death");
	sympos->sem_forks = sem_open("sem_forks", O_CREAT | O_EXCL, 0644,
			sympos->n_philos);
	if (sympos->sem_forks == SEM_FAILED)
		phb_quit_philo(sympos, 2, LU_RED1"Error: sem_open sem_forks\n"LU_END,
			CERR_MALLOC);
	sympos->sem_log = sem_open("sem_log", O_CREAT | O_EXCL, 0644, 1);
	if (sympos->sem_log == SEM_FAILED)
		phb_quit_philo(sympos, 2, LU_RED1"Error: sem_open sem_log\n"LU_END,
			CERR_MALLOC);
	sympos->sem_one_death = sem_open("sem_one_death", O_CREAT | O_EXCL,
			0644, 1);
	if (sympos->sem_one_death == SEM_FAILED)
		phb_quit_philo(sympos, 2, "Error: sem_open sem_one_death\n",
			CERR_MALLOC);
}

static void	st_get_tt_start(t_philo *philo, int n_philos)
{
	unsigned long	*tt_start;
	unsigned long	*tt_eat;

	tt_start = &(philo->agal->tt_start);
	tt_eat = &(philo->agal->tt_eat);
	if (philo->id == 1)
		*tt_start = 0;
	else if (philo->id % 2 == 0)
		*tt_start = *tt_eat;
	else if (philo->id % 2 != 0)
	{
		if (n_philos % 2 != 0)
			*tt_start = *tt_eat + *tt_eat;
		else
			*tt_start = 0;
	}
}

static void	st_get_tt_think(t_philo *philo, int n_philos)
{
	unsigned long	*tt_eat;
	unsigned long	*tt_sleep;
	unsigned long	*tt_think;

	tt_eat = &(philo->agal->tt_eat);
	tt_sleep = &(philo->agal->tt_sleep);
	tt_think = &(philo->agal->tt_think);
	if (n_philos % 2 == 0)
	{
		if (*tt_eat > *tt_sleep)
			*tt_think = *tt_eat - *tt_sleep;
		if (*tt_eat <= *tt_sleep)
			*tt_think = 0;
	}
	else if (n_philos % 2 != 0)
	{
		if (*tt_sleep >= (*tt_eat * 2))
			*tt_think = 0;
		else
			*tt_think = (*tt_eat * 2) - *tt_sleep;
	}
}

static void	st_init_philo_agalma(t_sympos *sympos, t_philo *philo,
	t_agalma *tmp)
{
	t_agalma	*agal;

	philo->agal = malloc(1 * sizeof(t_agalma));
	if (!philo->agal)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	agal = philo->agal;
	agal->n_meal = tmp->n_meal;
	agal->tt_eat = tmp->tt_eat;
	agal->tt_sleep = tmp->tt_sleep;
	agal->tt_die = tmp->tt_die;
	agal->st_time = phb_actualtime();
	st_get_tt_start(philo, sympos->n_philos);
	st_get_tt_think(philo, sympos->n_philos);
}

/*static void	st_init_philos(t_sympos *sympos, t_agalma *tmp)
{
	int	i;

	i = 0;
	sympos->philos = malloc(sympos->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].pid_philos = 0;
		sympos->philos[i].count_meal = 0;
		st_init_philo_agalma(sympos, &(sympos->philos[i]), tmp);
		i++;
	}
}*/

t_sympos	*phb_init_sympos(t_agalma *tmp, int n_philos)
{
	t_sympos	*sympos;
	int			i;

	sympos = malloc(1 * sizeof(t_sympos));
	if (!sympos)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	memset(sympos, 0, sizeof(t_sympos));
	sympos->n_philos = n_philos;
	i = 0;
	sympos->philos = malloc(sympos->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].pid_philos = 0;
		sympos->philos[i].count_meal = 0;
		st_init_philo_agalma(sympos, &(sympos->philos[i]), tmp);
		i++;
	}
	phb_init_semaphores(sympos);
	return (sympos);
}
