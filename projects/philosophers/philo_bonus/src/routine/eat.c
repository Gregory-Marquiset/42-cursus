/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:21:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

/*static int	ph_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lf_fork);
		if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
			return (pthread_mutex_unlock(philo->lf_fork), 1);
		pthread_mutex_lock(&philo->rg_fork);
		if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
		{
			pthread_mutex_unlock(philo->lf_fork);
			return (pthread_mutex_unlock(&philo->rg_fork), 1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->rg_fork);
		if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
			return (pthread_mutex_unlock(&philo->rg_fork), 1);
		pthread_mutex_lock(philo->lf_fork);
		if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
		{
			pthread_mutex_unlock(&philo->rg_fork);
			return (pthread_mutex_unlock(philo->lf_fork), 1);
		}
	}
	return (0);
}

static int	ph_check_even_die_while_eating(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;

	unsigned long (tt_die) = philo->agal->tt_die;
	unsigned long (tt_eat) = philo->agal->tt_eat;
	*(philo->kine->last_meal) = ph_actualtime();
	last_meal = *philo->kine->last_meal;
	tt_result = (((long long)ph_actualtime() - (long long)last_meal)
			+ (long long)tt_eat);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		if (ph_take_fork(philo))
			return (1);
		if (ph_speaking(philo->epis, philo->id, LPRO_EAT))
			return (1);
		ph_waiting(tt_die);
		pthread_mutex_unlock(philo->lf_fork);
		pthread_mutex_unlock(&philo->rg_fork);
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
		return (1);
	}
}

void	ph_eating(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_even_die_while_eating(philo);
	if (*alive != 0)
		return ;
	if (ph_take_fork(philo))
		return ;
	if (ph_speaking(philo->epis, philo->id, LPRO_EAT))
		return ;
	ph_waiting(philo->agal->tt_eat);
	pthread_mutex_unlock(philo->lf_fork);
	pthread_mutex_unlock(&philo->rg_fork);
	*(philo->kine->count_meal) += 1;
	if (philo->agal->n_meal > 0)
		if (*(philo->kine->count_meal) == philo->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
}*/
