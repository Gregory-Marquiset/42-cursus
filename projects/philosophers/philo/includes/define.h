/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:07:20 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:58:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

	//		code help		//
# define CERR_ARGS_H0 1
# define CERR_ARGS_H1 2

	//		code error		//
# define CERR_MALLOC 3
# define CERR_PT_CREAT 4
# define CERR_PT_JOIN 5
# define CERR_MU_INIT 6
# define CERR_GETTIME 7

	//		log utils		//
# define LU_GRAY "\033[1;30m"
# define LU_RED1 "\033[0;31m"
# define LU_RED2 "\033[1;31m"
# define LU_GRE1 "\033[0;32m"
# define LU_GRE2 "\033[1;32m"
# define LU_YEL1 "\033[0;33m"
# define LU_YEL2 "\033[1;33m"
# define LU_BLU1 "\033[0;34m"
# define LU_BLU2 "\033[1;34m"
# define LU_MAJ1 "\033[0;35m"
# define LU_MAJ2 "\033[1;35m"
# define LU_CYA1 "\033[0;36m"
# define LU_CYA2 "\033[1;36m"
# define LU_WHI1 "\033[0;37m"
# define LU_WHI2 "\033[1;37m"

# define LU_END "\033[0m"

	//		log error		//
# define LERR_ARGS_H0 "Error: One or more arguments are out of range!\n"
# define LERR_ARGS_H1 "Error: Bad argument format!\n"
# define LERR_MALLOC "Error: echec malloc\n"
# define LERR_PT_CREAT "Error: echec pthead_creat\n"
# define LERR_PT_JOIN "Error: echec pthead_join\n"
# define LERR_MU_INIT "Error: echec nutex_init\n"
# define LERR_GETTIME "Error: echec gettimeofday\n"

	//		project log		//
# define LPRO_FORK "has taken a fork\n"
# define LPRO_EAT "is eating\n"
# define LPRO_SLEEP "is sleeping\n"
# define LPRO_THINK "is thinking\n"
# define LPRO_DIED "died\n"

	//		test log		//
# define LTEST_TEST_3D "Test: %3d\n"
# define LTEST_TEST_0 "ceci est un Test 0\n"
# define LTEST_TEST_1 "ceci est un Test 1\n"
# define LTEST_TEST_2 "ceci est un Test 2\n"
# define LTEST_TEST_3 "ceci est un Test 2\n"

#endif
