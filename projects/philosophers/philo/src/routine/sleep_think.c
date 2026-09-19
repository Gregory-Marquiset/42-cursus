/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:20:55 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_check_die_while_thinking(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_die;
	unsigned long	tt_think;

	last_meal = *philo->kine->last_meal;
	tt_die = philo->agal->tt_die;
	tt_think = philo->agal->tt_think;
	tt_result = (long long)tt_die - ((long long)ph_actualtime()
			- (long long)last_meal);
	if (tt_result > 0 && tt_result < (long long)tt_die
		&& tt_result > (long long)tt_think)
		return (0);
	else
	{
		if (ph_speaking(philo->epis, philo->id, LPRO_THINK))
			return (1);
		ph_waiting(tt_die - ((long long)ph_actualtime()
				- (long long)last_meal), philo->kine->mtx_id_dead,
			philo->kine->id_dead);
		ph_modif_var(&(philo->epis->mtx_id_dead), philo->kine->id_dead,
			philo->id);
		return (1);
	}
}

void	ph_thinking(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_die_while_thinking(philo);
	if (*alive != 0)
		return ;
	if (ph_speaking(philo->epis, philo->id, LPRO_THINK))
		return ;
	ph_waiting(philo->agal->tt_think, philo->kine->mtx_id_dead,
		philo->kine->id_dead);
}

int	ph_check_die_while_sleeping(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->agal->tt_sleep;
	tt_die = philo->agal->tt_die;
	tt_result = (long long)tt_sleep + ((long long)ph_actualtime()
			- (long long)last_meal);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		if (ph_speaking(philo->epis, philo->id, LPRO_SLEEP))
			return (1);
		ph_waiting(tt_die - ((long long)ph_actualtime()
				- (long long)last_meal), philo->kine->mtx_id_dead,
			philo->kine->id_dead);
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead,
			philo->id);
		return (1);
	}
}

void	ph_sleeping(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_die_while_sleeping(philo);
	if (*alive != 0)
		return ;
	if (ph_speaking(philo->epis, philo->id, LPRO_SLEEP))
		return ;
	ph_waiting(philo->agal->tt_sleep, philo->kine->mtx_id_dead,
		philo->kine->id_dead);
}
