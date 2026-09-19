/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 12:44:42 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"
#include <sys/wait.h>

void	phb_kill_all(t_sympos *sympos)
{
	int	i;

	i = 0;
	while (i < sympos->n_philos)
	{
		if (sympos->philos[i].pid_philos > 0)
			kill(sympos->philos[i].pid_philos, SIGKILL);
		i++;
	}
}

static void	phb_init_helper(t_fork_helper *fhelper)
{
	fhelper->i = 0;
	fhelper->status = 0;
	fhelper->finished = 0;
	fhelper->code = 0;
	fhelper->pid = 0;
	fhelper->ended = 0;
}

static void	phb_wait_pid(t_sympos *sympos, t_fork_helper *fhelper)
{
	while (fhelper->finished < sympos->n_philos)
	{
		fhelper->ended = waitpid(-1, &fhelper->status, 0);
		if (fhelper->ended <= 0)
			break ;
		if (WIFEXITED(fhelper->status))
		{
			fhelper->code = WEXITSTATUS(fhelper->status);
			if (fhelper->code > 0)
			{
				phb_kill_all(sympos);
				break ;
			}
			else
				fhelper->finished++;
		}
	}
}

void	phb_forking(t_sympos *sympos)
{
	t_fork_helper	fhelper;

	phb_init_helper(&fhelper);
	while (fhelper.i < sympos->n_philos)
	{
		fhelper.pid = fork();
		if (fhelper.pid < 0)
			phb_quit_philo(sympos, 2, "fork failed\n", CERR_PT_CREAT);
		else if (fhelper.pid == 0)
		{
			phb_philo_routine(sympos, &sympos->philos[fhelper.i]);
			exit(0);
		}
		else
			sympos->philos[fhelper.i].pid_philos = fhelper.pid;
		fhelper.i++;
	}
	phb_wait_pid(sympos, &fhelper);
	phb_kill_all(sympos);
}
