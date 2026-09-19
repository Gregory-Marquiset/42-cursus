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

static int	ph_even_helper(t_philo *philo)
{
	if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
	{
		pthread_mutex_unlock(philo->lf_fork);
		return (philo->lf = false, 1);
	}
	if (!ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead))
	{
		pthread_mutex_lock(&philo->rg_fork);
		philo->rg = true;
	}
	else
	{
		pthread_mutex_unlock(philo->lf_fork);
		return (philo->lf = false, 1);
	}
	if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
	{
		pthread_mutex_unlock(philo->lf_fork);
		philo->lf = false;
		pthread_mutex_unlock(&philo->rg_fork);
		return (philo->rg = false, 1);
	}
	return (0);
}

static int	ph_odd_helper(t_philo *philo)
{
	if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
	{
		pthread_mutex_unlock(&philo->rg_fork);
		return (philo->rg = false, 1);
	}
	if (!ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead))
	{
		pthread_mutex_lock(philo->lf_fork);
		philo->lf = true;
	}
	else
	{
		pthread_mutex_unlock(&philo->rg_fork);
		return (philo->rg = false, 1);
	}
	if (ph_speaking(philo->epis, philo->id, LPRO_FORK))
	{
		pthread_mutex_unlock(&philo->rg_fork);
		philo->rg = false;
		pthread_mutex_unlock(philo->lf_fork);
		return (philo->lf = false, 1);
	}
	return (0);
}

static int	ph_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead))
		{
			pthread_mutex_lock(philo->lf_fork);
			philo->lf = true;
		}
		else
			return (1);
		if (ph_even_helper(philo))
			return (1);
	}
	else
	{
		if (!ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead))
		{
			pthread_mutex_lock(&philo->rg_fork);
			philo->rg = true;
		}
		else
			return (1);
		if (ph_odd_helper(philo))
			return (1);
	}
	return (0);
}

static int	ph_check_even_die_while_eating(t_philo *philo)
{
	unsigned long (tt_die) = philo->agal->tt_die;
	*(philo->kine->last_meal) = ph_actualtime();
	unsigned long (last_meal) = *philo->kine->last_meal;
	long long (tt_result) = (((long long)ph_actualtime() - (long long)last_meal)
			+ (long long)philo->agal->tt_eat);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		if (ph_take_fork(philo))
			return (1);
		if (ph_speaking(philo->epis, philo->id, LPRO_EAT))
		{
			pthread_mutex_unlock(philo->lf_fork);
			pthread_mutex_unlock(&philo->rg_fork);
			return (philo->lf = false, philo->rg = false, 1);
		}
		ph_waiting(tt_die, philo->kine->mtx_id_dead, philo->kine->id_dead);
		pthread_mutex_unlock(philo->lf_fork);
		philo->lf = false;
		pthread_mutex_unlock(&philo->rg_fork);
		philo->rg = false;
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
		return (1);
	}
}

void	ph_eating(t_philo *p, int *verif, int *alive)
{
	*verif = ph_take_var(p->kine->mtx_id_dead, p->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_even_die_while_eating(p);
	if (*alive != 0)
		return ;
	if (ph_take_fork(p))
		return ;
	if (ph_speaking(p->epis, p->id, LPRO_EAT))
	{
		pthread_mutex_unlock(p->lf_fork);
		p->lf = false;
		pthread_mutex_unlock(&p->rg_fork);
		p->rg = false;
		return ;
	}
	ph_waiting(p->agal->tt_eat, p->kine->mtx_id_dead, p->kine->id_dead);
	pthread_mutex_unlock(p->lf_fork);
	p->lf = false;
	pthread_mutex_unlock(&p->rg_fork);
	p->rg = false;
	*(p->kine->count_meal) += 1;
	if (p->agal->n_meal > 0)
		if (*(p->kine->count_meal) == p->agal->n_meal)
			ph_incr_var(p->kine->mtx_phs_meals, p->kine->phs_meals);
}
