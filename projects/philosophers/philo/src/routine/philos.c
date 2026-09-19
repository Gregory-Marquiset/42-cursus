/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:51 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static void	ph_starting_helper(t_philo *philo, unsigned long tt_die)
{
	pthread_mutex_lock(&philo->rg_fork);
	philo->rg = true;
	if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
	{
		pthread_mutex_unlock(&philo->rg_fork);
		philo->rg = false;
		return ;
	}
	ph_waiting(tt_die, philo->kine->mtx_id_dead, philo->kine->id_dead);
	pthread_mutex_unlock(&philo->rg_fork);
	philo->rg = false;
	ph_modif_var(philo->kine->mtx_id_dead,
		philo->kine->id_dead, philo->id);
}

int	ph_starting_philo(t_philo *philo, int *alive)
{
	unsigned long (tt_start) = philo->agal->tt_start;
	unsigned long (tt_die) = philo->agal->tt_die;
	while (*philo->epis->st_time > ph_actualtime())
		ph_waiting(1, philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (philo->agal->n_philos == 1)
	{
		ph_starting_helper(philo, tt_die);
		return (1);
	}
	if (tt_start < tt_die)
		ph_waiting(tt_start, philo->kine->mtx_id_dead, philo->kine->id_dead);
	else
	{
		ph_waiting(tt_die, philo->kine->mtx_id_dead, philo->kine->id_dead);
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
	}
	*alive = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	return (0);
}

void	*ph_routine_philos(void *arg)
{
	t_philo *(philo) = (t_philo *)arg;
	int (verif) = 0;
	int (alive) = 0;
	if (ph_starting_philo(philo, &alive))
		return (NULL);
	while (!verif && !alive)
	{
		ph_eating(philo, &verif, &alive);
		if (verif || alive)
			break ;
		ph_sleeping(philo, &verif, &alive);
		if (verif || alive)
			break ;
		ph_thinking(philo, &verif, &alive);
	}
	if (philo->lf)
		pthread_mutex_unlock(philo->lf_fork);
	if (philo->rg)
		pthread_mutex_unlock(&philo->rg_fork);
	return (NULL);
}
