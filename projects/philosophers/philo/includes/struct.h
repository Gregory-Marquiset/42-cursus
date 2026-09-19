/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:54:55 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

		//		episkopos		//

typedef struct s_epis
{
	pthread_t		thread_ep;
	pthread_mutex_t	mtx_verif;
	int				*verif;
	pthread_mutex_t	mtx_printf;
	pthread_mutex_t	mtx_id_dead;
	int				*id_dead;
	pthread_mutex_t	mtx_phs_meals;
	int				*phs_meals;
	unsigned long	*st_time;
	int				n_meal;
	int				n_philos;
}				t_epis;

		//		philo		//

typedef struct s_agalma
{
	int				n_philos;
	int				n_meal;
	unsigned long	st_time;
	unsigned long	tt_start;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	unsigned long	tt_think;
	unsigned long	tt_die;
}				t_agalma;

typedef struct s_kinesis
{
	unsigned long	*last_meal;
	int				*count_meal;
	pthread_mutex_t	*mtx_phs_meals;
	int				*phs_meals;
	pthread_mutex_t	*mtx_id_dead;
	int				*id_dead;
}				t_kinesis;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_ph;
	t_agalma		*agal;
	t_kinesis		*kine;
	t_epis			*epis;
	bool			lf;
	pthread_mutex_t	*lf_fork;
	bool			rg;
	pthread_mutex_t	rg_fork;
}				t_philo;

		//		symposium		//

typedef struct s_sympos
{
	t_epis	*epis;
	t_philo	*philos;
}				t_sympos;

#endif
