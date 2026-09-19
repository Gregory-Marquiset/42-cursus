SRCS = srcs/main.cpp \
	srcs/Harl.cpp
INCLUDES = -Iincludes
NAME = harl
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP
RM = rm -rf
MK = mkdir -p

YELLOW = \033[1;33m
GREEN = \033[1;32m
CYAN = \033[1;36m
RESET = \033[0m

OBJ_DIR = obj/
DEP_DIR = dep/
OBJ = $(SRCS:.cpp=.o)
OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))

DEPENDENCIES = $(OBJ_PREF:.o=.d)

all: $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@echo "$(YELLOW)Compiling $(RESET)$(CYAN)$<$(RESET)..."
	@$(MK) $(dir $@) $(DEP_DIR)$(dir $<)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD -MF $(DEP_DIR)$*.d

$(NAME): $(OBJ_PREF)
	@echo "$(YELLOW)Linking $(CYAN)$(NAME)$(RESET)..."
	$(CC) $(CFLAGS) $(OBJ_PREF) -o $(NAME)
	@echo "$(GREEN)Executable $(CYAN)$(NAME)$(GREEN) successfully created!$(RESET)"


clean:
	@echo "$(YELLOW)Cleaning object files and dependencies $(CYAN)$(OBJ_DIR) $(DEP_DIR)$(RESET)..."
	$(RM) $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	@echo "$(YELLOW)Removing executable $(CYAN)$(NAME)$(RESET)..."
	$(RM) $(NAME)

re: fclean all

-include $(DEPENDENCIES)

.PHONY: all clean fclean re
