/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:02 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ts_print_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->epis->mtx_printf);
	printf("philo[%2d] sur n_philo %3d\n"
		"n_meal %2d, tt_star %ld\n"
		"tt_eat %ld, tt_sleep %ld\n"
		"tt_think %ld, tt_die %ld\n\n", philo->id, philo->agal->n_philos,
		philo->agal->n_meal, philo->agal->tt_start,
		philo->agal->tt_eat, philo->agal->tt_sleep,
		philo->agal->tt_think, philo->agal->tt_die);
	pthread_mutex_unlock(&philo->epis->mtx_printf);
}

void	ts_print_philos_infos(t_sympos *sympos)
{
	int (i) = 0;
	int (n_philo) = sympos->philos[0].agal->n_philos;
	pthread_mutex_lock(&sympos->epis->mtx_printf);
	while (i < n_philo)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nhe start at "
			"%ld and think %ld\n" LU_END,
			sympos->philos[i].id, sympos->philos[i].agal->tt_start,
			sympos->philos[i].agal->tt_think);
		if (sympos->philos[0].agal->n_philos > 1)
		{
			printf(LU_YEL1 "lf_fork = %14p" LU_END,
				(void *)sympos->philos[i].lf_fork);
		}
		else
			printf(LU_YEL1 "lf_fork = NULL" LU_END);
		printf(LU_YEL1 " | rg_fork = %14p\n\n" LU_END,
			(void *)&sympos->philos[i].rg_fork);
		i++;
	}
	pthread_mutex_unlock(&sympos->epis->mtx_printf);
}

void	ts_print_sympos(t_sympos *sympos)
{
	pthread_mutex_lock(&sympos->epis->mtx_printf);
	printf(LU_BLU1 "Episkopos watches the symposium:\n"
		"He speak at %14p for %d philosophers\ntt_die: %ld\ntt_eat: %ld\n"
		"tt_sleep: %ld\nn_meal: %d\n" LU_END,
		(void *)&sympos->epis->mtx_printf, sympos->epis->n_philos,
		sympos->philos[0].agal->tt_die, sympos->philos[0].agal->tt_eat,
		sympos->philos[0].agal->tt_sleep, sympos->epis->n_meal);
	pthread_mutex_unlock(&sympos->epis->mtx_printf);
	ts_print_philos_infos(sympos);
}
