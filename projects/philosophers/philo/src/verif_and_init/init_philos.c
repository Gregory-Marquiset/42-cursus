/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:20:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:30 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static void	ph_get_tt_start(t_philo *philo)
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
		if (philo->agal->n_philos % 2 != 0)
			*tt_start = *tt_eat + *tt_eat;
		else
			*tt_start = 0;
	}
}

static void	ph_get_tt_think(t_philo *philo)
{
	unsigned long	*tt_eat;
	unsigned long	*tt_sleep;
	unsigned long	*tt_think;

	tt_eat = &(philo->agal->tt_eat);
	tt_sleep = &(philo->agal->tt_sleep);
	tt_think = &(philo->agal->tt_think);
	if (philo->agal->n_philos % 2 == 0)
	{
		if (*tt_eat > *tt_sleep)
			*tt_think = *tt_eat - *tt_sleep;
		if (*tt_eat <= *tt_sleep)
			*tt_think = 0;
	}
	else if (philo->agal->n_philos % 2 != 0)
	{
		if (*tt_sleep >= (*tt_eat * 2))
			*tt_think = 0;
		else
			*tt_think = (*tt_eat * 2) - *tt_sleep;
	}
}

static void	ph_init_philo_agalma(t_sympos *sympos, t_philo *philo,
	t_agalma *tmp)
{
	t_agalma	*agal;

	philo->agal = ph_init_malloc(sympos, 1, sizeof(t_agalma));
	agal = philo->agal;
	agal->n_philos = tmp->n_philos;
	agal->n_meal = tmp->n_meal;
	agal->tt_eat = tmp->tt_eat;
	agal->tt_sleep = tmp->tt_sleep;
	agal->tt_die = tmp->tt_die;
	ph_get_tt_start(philo);
	ph_get_tt_think(philo);
}

static void	ph_init_philo_kine(t_sympos *sympos, t_philo *philo)
{
	philo->kine = ph_init_malloc(sympos, 1, sizeof(t_kinesis));
	philo->kine->last_meal = ph_init_malloc(sympos, 1, sizeof(unsigned long));
	*(philo->kine->last_meal) = ph_actualtime();
	philo->kine->count_meal = ph_init_malloc(sympos, 1, sizeof(int));
	*(philo->kine->count_meal) = 0;
	philo->kine->phs_meals = sympos->epis->phs_meals;
	philo->kine->mtx_phs_meals = &(sympos->epis->mtx_phs_meals);
	philo->kine->id_dead = sympos->epis->id_dead;
	philo->kine->mtx_id_dead = &(sympos->epis->mtx_id_dead);
}

void	ph_init_philos(t_sympos *sympos, t_agalma *tmp)
{
	int	i;

	i = 0;
	sympos->philos = ph_init_malloc(sympos, tmp->n_philos,
			sizeof(t_philo));
	while (i < tmp->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		ph_init_philo_agalma(sympos, &(sympos->philos[i]), tmp);
		ph_init_philo_kine(sympos, &(sympos->philos[i]));
		sympos->philos[i].epis = sympos->epis;
		if (i == 0)
			ph_init_fork(sympos, &sympos->philos[i], NULL, 0);
		else
			ph_init_fork(sympos, &sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (tmp->n_philos > 1)
		ph_init_fork(sympos, &sympos->philos[0], &sympos->philos[i - 1], 2);
}
