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
	printf("philo[%2d]\n"
		"n_meal %2d, tt_star %ld\n"
		"tt_eat %ld, tt_sleep %ld\n"
		"tt_think %ld, tt_die %ld\n\n", philo->id,
		philo->agal->n_meal, philo->agal->tt_start,
		philo->agal->tt_eat, philo->agal->tt_sleep,
		philo->agal->tt_think, philo->agal->tt_die);
}

void	ts_print_philos_infos(t_sympos *sympos)
{
	int	i;

	i = 0;
	while (i < sympos->n_philos)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nhe start at "
			"%ld and think %ld\n" LU_END,
			sympos->philos[i].id, sympos->philos[i].agal->tt_start,
			sympos->philos[i].agal->tt_think);
		i++;
	}
}

void	ts_print_sympos(t_sympos *sympos)
{
	printf(LU_BLU1 "The symposium is open:\n"
		"For %d philosophers\ntt_die: %ld\ntt_eat: %ld\n"
		"tt_sleep: %ld\nn_meal: %d\n" LU_END,
		sympos->n_philos, sympos->philos[0].agal->tt_die,
		sympos->philos[0].agal->tt_eat, sympos->philos[0].agal->tt_sleep,
		sympos->philos[0].agal->n_meal);
	ts_print_philos_infos(sympos);
}
