/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:14:11 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 12:22:17 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	phb_micro_sleep(t_sympos *sympos, t_philo *philo,
	unsigned long ms, unsigned long *last_meal_time)
{
	unsigned long	start;
	unsigned long	now;

	start = phb_actualtime();
	while (1)
	{
		usleep(ms / 10);
		now = phb_actualtime();
		if ((now - *last_meal_time) > philo->agal->tt_die)
		{
			phb_speaking_for_dead(sympos, philo->id);
			exit(philo->id);
		}
		if ((now - start) >= ms)
			break ;
	}
}

static void	phb_routine_helper(t_sympos *sympos, t_philo *philo,
	unsigned long *last_meal_time)
{
	sem_wait(sympos->sem_forks);
	phb_speaking(sympos, philo->id, LPRO_FORK);
	sem_wait(sympos->sem_forks);
	phb_speaking(sympos, philo->id, LPRO_FORK);
	phb_speaking(sympos, philo->id, LPRO_EAT);
	*last_meal_time = phb_actualtime();
	phb_micro_sleep(sympos, philo, philo->agal->tt_eat, last_meal_time);
	sem_post(sympos->sem_forks);
	sem_post(sympos->sem_forks);
	if (philo->agal->n_meal != -1)
	{
		philo->count_meal++;
		if (philo->count_meal == philo->agal->n_meal)
			exit(0);
	}
	phb_speaking(sympos, philo->id, LPRO_SLEEP);
	phb_micro_sleep(sympos, philo, philo->agal->tt_sleep, last_meal_time);
	phb_speaking(sympos, philo->id, LPRO_THINK);
	if (philo->agal->tt_think > 0)
		phb_micro_sleep(sympos, philo, philo->agal->tt_think,
			last_meal_time);
}

void	phb_philo_routine(t_sympos *sympos, t_philo *philo)
{
	unsigned long	last_meal_time;
	unsigned long	now;

	last_meal_time = phb_actualtime();
	if (sympos->n_philos == 1)
	{
		sem_wait(sympos->sem_forks);
		phb_speaking(sympos, philo->id, LPRO_FORK);
		phb_waiting(philo->agal->tt_die);
		sem_post(sympos->sem_forks);
		phb_speaking_for_dead(sympos, philo->id);
		exit(philo->id);
	}
	phb_waiting(philo->agal->tt_start);
	while (1)
	{
		phb_routine_helper(sympos, philo, &last_meal_time);
		now = phb_actualtime();
		if ((now - last_meal_time) > philo->agal->tt_die)
		{
			phb_speaking_for_dead(sympos, philo->id);
			exit(philo->id);
		}
	}
}
