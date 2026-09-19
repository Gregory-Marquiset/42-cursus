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

static int	st_atoi_safe(char *str)
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
			phb_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			phb_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		phb_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	else if (result < 1)
		phb_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	return ((int)result);
}

static int	st_strncmp(const char *s1, const char *s2, unsigned long n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	st_program_run_helper(char *argv_1)
{
	if (!st_strncmp(argv_1, "--help", 7))
		phb_quit_philo(NULL, 2, LERR_ARGS_H3, CERR_ARGS_H1);
}

t_sympos	*phb_args_verif_and_make_sympos(int argc, char **argv)
{
	t_agalma	tmp;
	int			n_philos;

	if (argc == 2)
		st_program_run_helper(argv[1]);
	if (argc < 5 || argc > 6)
		phb_quit_philo(NULL, 2, LERR_ARGS_H1, CERR_ARGS_H1);
	n_philos = st_atoi_safe(argv[1]);
	tmp.tt_die = (unsigned long)st_atoi_safe(argv[2]);
	tmp.tt_eat = (unsigned long)st_atoi_safe(argv[3]);
	tmp.tt_sleep = (unsigned long)st_atoi_safe(argv[4]);
	if (n_philos > 200 || tmp.tt_die < 60 || tmp.tt_eat < 60
		|| tmp.tt_sleep < 60)
		phb_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	if (argv[5])
		tmp.n_meal = st_atoi_safe(argv[5]);
	else
		tmp.n_meal = -1;
	tmp.tt_start = 0;
	tmp.tt_think = 0;
	return (phb_init_sympos(&tmp, n_philos));
}
