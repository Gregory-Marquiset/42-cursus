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

	//		log help		//
# define LERR_ARGS_H3 LU_BLU2 "\nHere some details about the project philo:\n" LU_END \
"\tthe project calls for creating a symposium of philosophers\n\
\twho eat, think and sleep continuously in the same dish\n\
\tbut with a limited number of fork and must therefore\n\
\teat in turns so as not to die of hunger.\n\n" \
LU_BLU2 "For run project philo you need 5 or 6 arguments\n" LU_END \
"\t1: program_name -> The program name\n\
\t2: number_of_philosophers -> The number of philosopher you want\n\
\t3: time_to_die -> Time max between each philosopher meal\n\
\t4: time_to_eat -> Time needed by a philosopher for eating a meal\n\
\t5: time_to_sleep -> Time spent sleeping\n\
\t6: (optional)number_of_times_each_philosopher_must_eat -> Number of meal for each philo,\n\
\t\twhen reached program stop, ifndef run until one philo die\n\n" \
LU_YEL1 "Number of philos most be between 1 and 200\n\
Number of meal most be between 1 and int max\n\
All time values most be between 60 and int max\n\
All time values are in milliseconds\n\n" LU_END \
LU_BLU2 "\t\t<-----| TIPS |----->\n" LU_END \
"If you want to test this program with a visualizer, you can use this site:\n" \
LU_CYA2 "\thttps://nafuka11.github.io/philosophers-visualizer/\n\n" LU_END \
"If you want to test 'philo' more easily without manually copying and pasting,\n" \
"this two bash lines copy the output from 'philo' so you can paste it easily.\n" \
"It's similar to using the right click to copy but it's faster.\n" \
"The lines also removes color codes from the output because " \
"they are not accepted by the site.\n\n" LU_END \
"The first one is to be used with a specified number of meals:\n" \
LU_YEL1 "\t./philo n_philo tt_die tt_eat tt_sleep n_meal " \
"| sed -r 's/\\x1B[[0-9;]*[A-Za-z]//g' | xclip -selection c\n\n" LU_END \
"The second one is to be used without a specified number of meals but with a timeout:\n" \
LU_YEL1 "\ttimeout 10 ./philo n_philo tt_die tt_eat tt_sleep 2>&1 " \
"| sed -r 's/\\x1B[[0-9;]*[A-Za-z]//g' | cat | xclip -selection c\n\n" LU_END

	//		log error		//
# define LERR_ARGS_H0 LU_RED2 "Error: " LU_END "One or more arguments are out of range!\n" LU_BLU2 "For help run: " LU_END "./philo --help++\n"
# define LERR_ARGS_H1 LU_RED2 "Error: " LU_END "Bad argument format!\n" LU_BLU2 "For help run: " LU_END "./philo --help\n"
# define LERR_MALLOC LU_RED1 "Error: echec malloc\n" LU_END
# define LERR_PT_CREAT LU_RED1 "Error: echec pthead_creat\n" LU_END
# define LERR_PT_JOIN LU_RED1 "Error: echec pthead_join\n" LU_END
# define LERR_MU_INIT LU_RED1 "Error: echec nutex_init\n" LU_END
# define LERR_GETTIME LU_RED1 "Error: echec gettimeofday\n" LU_END

	//		project log		//
# define LPRO_JSYM LU_GRE1 "join the symposium\n" LU_END
# define LPRO_LSYM LU_GRE1 "left the symposium\nsymposium" LU_END
# define LPRO_FORK "has taken a fork\n"
# define LPRO_MEAL "all meal as bean eaten\n\n"
# define LPRO_EAT "is eating\n"
# define LPRO_SLEEP "is sleeping\n"
# define LPRO_THINK "is thinking\n"
# define LPRO_DIED "died\n"

	//		test log		//
# define LTEST_TEST_3D LU_YEL2 "Test: %3d\n" LU_END
# define LTEST_TEST_0 LU_YEL2 "ceci est un Test 0\n" LU_END
# define LTEST_TEST_1 LU_YEL2 "ceci est un Test 1\n" LU_END
# define LTEST_TEST_2 LU_YEL2 "ceci est un Test 2\n" LU_END
# define LTEST_TEST_3 LU_YEL2 "ceci est un Test 2\n" LU_END

#endif
