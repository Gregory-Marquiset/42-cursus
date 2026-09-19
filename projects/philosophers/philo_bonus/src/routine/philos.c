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

/*int	ph_starting_philo(t_philo *philo, int *alive)
{
	unsigned long (tt_start) = philo->agal->tt_start;
	unsigned long (tt_die) = philo->agal->tt_die;
	while (*philo->epis->st_time > ph_actualtime())
		ph_waiting(1);
	if (philo->agal->n_philos == 1)
	{
		pthread_mutex_lock(&philo->rg_fork);
		if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
			return (pthread_mutex_unlock(&philo->rg_fork), 1);
		ph_waiting(tt_die);
		pthread_mutex_unlock(&philo->rg_fork);
		ph_modif_var(philo->kine->mtx_id_dead,
			philo->kine->id_dead, philo->id);
	}
	if (tt_start < tt_die)
		ph_waiting(tt_start);
	else
	{
		ph_waiting(tt_die);
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
	}
	*alive = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	return (0);
}

void	*ph_routine_philos(void *tmp)
{
	t_philo (*philo) = (t_philo *)tmp;
	int (verif) = 0;
	int (alive) = 0;
	alive = ph_starting_philo(philo, &alive);
	while (verif == 0 && alive == 0)
	{
		ph_eating(philo, &verif, &alive);
		if (verif != 0 || alive != 0)
			return (NULL);
		ph_sleeping(philo, &verif, &alive);
		if (verif != 0 || alive != 0)
			return (NULL);
		ph_thinking(philo, &verif, &alive);
	}
	return (NULL);
}*/
