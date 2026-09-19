# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 17:10:22 by gmarquis          #+#    #+#              #
#    Updated: 2023/11/23 16:49:21 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_bzero.c $\
ft_isalpha.c $\
ft_isprint.c $\
ft_memcmp.c $\
ft_memset.c $\
ft_putnbr_fd.c $\
ft_strchr.c $\
ft_strjoin.c $\
ft_strlen.c $\
ft_strnstr.c $\
ft_substr.c $\
ft_calloc.c $\
ft_isascii.c $\
ft_itoa.c $\
ft_memcpy.c $\
ft_putchar_fd.c $\
ft_putstr_fd.c $\
ft_strdup.c $\
ft_strlcat.c $\
ft_strmapi.c $\
ft_strrchr.c $\
ft_tolower.c $\
ft_atoi.c $\
ft_isalnum.c $\
ft_isdigit.c $\
ft_memchr.c $\
ft_memmove.c $\
ft_putendl_fd.c $\
ft_split.c $\
ft_striteri.c $\
ft_strlcpy.c $\
ft_strncmp.c $\
ft_strtrim.c $\
ft_toupper.c

SRCS_BNS = ft_lstadd_back_bonus.c $\
ft_lstadd_front_bonus.c $\
ft_lstclear_bonus.c $\
ft_lstdelone_bonus.c $\
ft_lstiter_bonus.c $\
ft_lstlast_bonus.c $\
ft_lstmap_bonus.c $\
ft_lstnew_bonus.c $\
ft_lstsize_bonus.c $\
$(SRCS)

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS))

OBJS_BNS = $(SRCS_BNS:.c=.o)
OBJS_BNS_PREF = $(addprefix $(OBJS_DIR), $(OBJS_BNS))

NAME = libft.a

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c libft.h
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF) $(OBJS_BNS_PREF)
	@ar r $@ $^

all : $(NAME)

bonus : $(OBJS_BNS_PREF)
	@ar r $(NAME) $(OBJS_BNS_PREF)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
