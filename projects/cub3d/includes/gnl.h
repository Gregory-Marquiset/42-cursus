/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 08:17:52 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/25 21:32:59 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_gnl
{
	int		value;
	int		len;
	char	*line;
	char	*stock_line;
	char	*new_line;
	char	*dest;
}	t_gnl;

/*GNL*/
char	*gnl(int fd);

/*Utils*/
int		ft_len(char *s);
int		ft_check(char *stat);
char	*copy(char *src);
char	*join(char *s1, char *s2, t_gnl gnl);

#endif
