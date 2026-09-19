/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:36:59 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_threading(t_sympos *sympos)
{
	int (i) = 0;
	int (n_philos) = sympos->epis->n_philos;
	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	usleep(2);
	while (i < n_philos)
	{
		ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_philos,
			&sympos->philos[i]);
		usleep(2);
		i++;
	}
	i = 0;
	while (i < n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		usleep(5);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	usleep(2);
}
