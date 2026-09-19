/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:30:09 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:35 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	*ph_init_malloc_mutex(t_sympos *sympos, pthread_mutex_t *mutex,
	int nbr, size_t var_size)
{
	void	*ptr;

	ptr = malloc(nbr * var_size);
	if (!ptr)
	{
		pthread_mutex_unlock(mutex);
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	}
	return (ptr);
}

void	*ph_init_malloc(t_sympos *sympos, int nbr, size_t var_size)
{
	void	*ptr;

	ptr = malloc(nbr * var_size);
	if (!ptr)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	memset(ptr, 0, nbr * var_size);
	return (ptr);
}

void	ph_init_thread(t_sympos *sympos, pthread_t *thread, void *fun,
	void *arg)
{
	if (pthread_create(&*(thread), NULL, fun, arg))
		ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
}

void	ph_init_mtx(t_sympos *sympos, pthread_mutex_t *mtx)
{
	if (pthread_mutex_init(mtx, NULL))
		ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
}

void	ph_init_fork(t_sympos *sympos, t_philo *philo, t_philo *lf_philo,
	int pos)
{
	if (pos == 0)
	{
		ph_init_mtx(sympos, &philo->rg_fork);
		philo->lf_fork = NULL;
	}
	else if (pos == 1)
	{
		ph_init_mtx(sympos, &philo->rg_fork);
		philo->lf_fork = &(lf_philo->rg_fork);
	}
	else if (pos == 2)
		philo->lf_fork = &(lf_philo->rg_fork);
	philo->rg = false;
	philo->lf = false;
}
