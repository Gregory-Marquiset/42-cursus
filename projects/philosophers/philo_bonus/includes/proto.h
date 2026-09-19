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
# include <semaphore.h>
# include <fcntl.h>

# include "struct.h"
# include "define.h"

/*_________________________________________________*/

//		ROUTINE				//

		//		philos.c		//
/*void			*ph_routine_philos(void *tmp);

		//	sleep_think.c	//
int				ph_starting_philo(t_philo *philo, int *alive);
void			ph_thinking(t_philo *philo, int *verif, int *alive);
void			ph_sleeping(t_philo *philo, int *verif, int *alive);

		//		eat.c		//
void			ph_eating(t_philo *philo, int *verif, int *alive);*/

/*_________________________________________________*/

//		VERIF_AND_INIT		//

		//	args_verif.c	//
t_sympos		*phb_args_verif_and_make_sympos(int argc, char **argv);

		//	init.c			//
t_sympos		*phb_init_sympos(t_agalma *tmp, int n_philos);

/*_________________________________________________*/

		//	act.c			//
//void			phb_waiting(unsigned long time);

		//	out.c			//
void			phb_quit_philo(t_sympos *sympos, int fd_out, char *message,
					int error_code);

		//	test_file.c		//
void			ts_print_philo(t_philo *philo);
void			ts_print_sympos(t_sympos *sympos);

		//	forking.c		//
void			phb_forking(t_sympos *sympos);

		//	utils.c			//
void			phb_speaking(t_sympos *sympos, int philo_id, char *msg);
void			phb_speaking_for_dead(t_sympos *sympos, int philo_id);
unsigned long	phb_actualtime(void);
void			phb_waiting(unsigned long time);

		//	routine.c		//
void	phb_philo_routine(t_sympos *sympos, t_philo *philo);

#endif
