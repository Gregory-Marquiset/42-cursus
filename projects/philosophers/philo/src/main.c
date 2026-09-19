/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:09 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	main(int argc, char **argv)
{
	t_sympos	*sympos;

	sympos = ph_args_verif_and_make_sympos(argc, argv);
	ph_threading(sympos);
	ph_quit_philo(sympos, 1, NULL, 0);
}
