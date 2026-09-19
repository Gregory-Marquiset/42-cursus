/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:48 by gmarquis          #+#    #+#             */
/*   Updated: 2025/01/08 12:49:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	main(int argc, char **argv)
{
	t_sympos	*sympos;

	sympos = phb_args_verif_and_make_sympos(argc, argv);
	phb_forking(sympos);
	phb_quit_philo(sympos, 1, NULL, 0);
}
