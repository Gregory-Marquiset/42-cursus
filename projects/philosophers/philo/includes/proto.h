/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:42:43 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include "struct.h"
# include "define.h"

/*_________________________________________________*/

//		ROUTINE				//

		//		epis.c		//
void			*ph_routine_epis(void *tmp);

		//		philos.c		//
void			*ph_routine_philos(void *tmp);

		//	sleep_think.c	//
int				ph_starting_philo(t_philo *philo, int *alive);
void			ph_thinking(t_philo *philo, int *verif, int *alive);
void			ph_sleeping(t_philo *philo, int *verif, int *alive);

		//		eat.c		//
void			ph_eating(t_philo *philo, int *verif, int *alive);

/*_________________________________________________*/

//		VERIF_AND_INIT		//

		//	args_verif.c	//
t_sympos		*ph_args_verif_and_make_sympos(int argc, char **argv);

		//	init.c			//
t_sympos		*ph_init_sympos(t_agalma *tmp);

		//	init_philos.c	//
void			ph_init_philos(t_sympos *sympos, t_agalma *tmp);

		//	init_utils.c	//
void			*ph_init_malloc_mutex(t_sympos *sympos, pthread_mutex_t *mutex,
					int nbr, size_t var_size);
void			*ph_init_malloc(t_sympos *sympos, int nbr, size_t var_size);
void			ph_init_thread(t_sympos *sympos, pthread_t *thread, void *fun,
					void *arg);
void			ph_init_mtx(t_sympos *sympos, pthread_mutex_t *mtx);
void			ph_init_fork(t_sympos *sympos, t_philo *philo,
					t_philo *rg_philo, int pos);

/*_________________________________________________*/

		//	act.c			//
int				ph_check_printf_verif(t_epis *epis);
int				ph_speaking(t_epis *epis, int id, char *message);
void			ph_waiting(unsigned long time, pthread_mutex_t *mutex,
					int *var);

		//	out.c			//
void			ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
					int error_code);

		//	test_file.c		//
void			ts_print_philo(t_philo *philo);
void			ts_print_sympos(t_sympos *sympos);

		//	threading.c		//
void			ph_threading(t_sympos *sympos);

		//	utils.c			//
int				ph_take_var(pthread_mutex_t *mutex, int *var);
void			ph_incr_var(pthread_mutex_t *mutex, int *var);
void			ph_modif_var(pthread_mutex_t *mutex, int *dest, int src);
unsigned long	ph_actualtime(void);

#endif
