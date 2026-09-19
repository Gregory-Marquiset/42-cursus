# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 22:14:21 by gmarquis          #+#    #+#              #
#    Updated: 2023/12/21 02:51:08 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fonction_1_bonus.c $\
fonction_2_bonus.c $\
fonction_3_bonus.c $\
fonction_4_bonus.c $\
fonction_5_bonus.c $\
fonction_6_bonus.c $\
fonction_7_bonus.c $\
fonction_8_bonus.c $\
fonction_9_bonus.c $\
fonction_10_bonus.c $\
fonction_11_bonus.c $\
fonction_12_bonus.c $\
fonction_13_bonus.c $\
fonction_14_bonus.c $\
fonction_15_bonus.c $\
fonction_16_bonus.c $\
fonction_17_bonus.c $\
fonction_18_bonus.c $\
fonction_19_bonus.c $\
fonction_digit_bonus.c $\
fonction_space_bonus.c $\
fonction_dot_bonus.c $\
fonction_hexa_bonus.c $\
fonction_len_bonus.c $\
fonction_put_bonus.c $\
fonction_symbol_bonus.c $\
fonction_verif_bonus.c $\
ft_printf.c

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS))

NAME = libftprintf.a

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c ft_printf.h
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF)
	@ar r $@ $^

all : $(NAME)

bonus : all

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
