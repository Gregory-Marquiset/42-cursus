# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2025/01/08 12:20:18 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/forking.c \
	src/main.c \
	src/out.c \
	src/test_file.c \
	src/utils.c

SRC_ROUTINE = src/routine/routine.c \
	src/routine/philos.c \
	src/routine/eat.c

SRC_VI = src/verif_and_init/args_verif.c \
	src/verif_and_init/init.c

INCLUDES = -Iincludes

NAME = philo_bonus

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -fPIC
#-fsanitize=thread (ralenti beaucoup le programme et creer des erreur, a ne pas combiner avec valgrind)
PHFLAGS = -pthread
#valgrind --tool=helgrind --history-level=full
ARGS = 199 210 60 60 25
RM = rm -rf

OBJ_DIR = obj/
DEP_DIR = dep/
OBJ = $(SRC:.c=.o)
OBJ_ROUTINE = $(SRC_ROUTINE:.c=.o)
OBJ_VI = $(SRC_VI:.c=.o)

OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_ROUTINE_PREF = $(addprefix $(OBJ_DIR), $(OBJ_ROUTINE))
OBJ_VI_PREF = $(addprefix $(OBJ_DIR), $(OBJ_VI))

DEPENDENCIES = $(patsubst $(OBJ_DIR)%.o,$(DEP_DIR)%.d,$(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_VI_PREF))

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@$(MK) -p $(dir $@) $(DEP_DIR)$(dir $<)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@ -MMD -MF $(DEP_DIR)$*.d

$(NAME) : $(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_VI_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) $(OBJ_DIR) $(DEP_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re v

-include $(DEPENDENCIES)

