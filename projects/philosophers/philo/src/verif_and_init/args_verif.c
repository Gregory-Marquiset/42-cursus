/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:00:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:25 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ph_atoi_safe(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	else if (result < 1)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	return ((int)result);
}

t_sympos	*ph_args_verif_and_make_sympos(int argc, char **argv)
{
	t_agalma	tmp;

	if (argc < 5 || argc > 6)
		ph_quit_philo(NULL, 2, LERR_ARGS_H1, CERR_ARGS_H1);
	tmp.n_philos = ph_atoi_safe(argv[1]);
	tmp.tt_die = (unsigned long)ph_atoi_safe(argv[2]);
	tmp.tt_eat = (unsigned long)ph_atoi_safe(argv[3]);
	tmp.tt_sleep = (unsigned long)ph_atoi_safe(argv[4]);
	if (tmp.n_philos > 200 || tmp.tt_die < 60 || tmp.tt_eat < 60
		|| tmp.tt_sleep < 60)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	if (argv[5])
		tmp.n_meal = ph_atoi_safe(argv[5]);
	else
		tmp.n_meal = -1;
	tmp.tt_start = 0;
	tmp.tt_think = 0;
	return (ph_init_sympos(&tmp));
}
