NAME = cub3D
NAME_BONUS = cub3D_bonus
C = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD

############################Sources########################
SRCS_DIR = srcs/

FILES = cub3d

LIBFT_DIR = ft_from_libft/
LIBFT_FILES = ft_bzero ft_calloc ft_strlen ft_strcmp ft_strncmp\
				ft_strndup ft_split ft_strchr ft_atol ft_strnstr
LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(LIBFT_FILES))

GNL_DIR = gnl/
GNL_FILES = gnl gnl_utils
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))

PARSE_DIR = parsing/
PARSE_FILES = parse_file parse_utils parse_textures_verif parse_textures\
				parse_colours parse_map get_map map_line_helper
PARSE_SRCS = $(addprefix $(PARSE_DIR), $(PARSE_FILES))

GAME_DIR = game/
GAME_FILES = collision game move render_utils render
GAME_SRCS = $(addprefix $(GAME_DIR), $(GAME_FILES))

CLEANING_DIR = cleaning_and_errors/
CLEANING_FILES = cleaning error_msg
CLEANING_SRCS = $(addprefix $(CLEANING_DIR), $(CLEANING_FILES))


SRCS = $(FILES) $(LIBFT_SRCS) $(GNL_SRCS) $(PARSE_SRCS) $(CLEANING_SRCS) $(GAME_SRCS)

############################Sources_Bonus########################
SRCS_DIR_B = srcs_bonus/

FILES_B = cub3d

LIBFT_DIR_B = ft_from_libft/
LIBFT_FILES_B = ft_bzero ft_calloc ft_strlen ft_strcmp ft_strncmp\
				ft_strndup ft_split ft_strchr ft_atol ft_strnstr
LIBFT_SRCS_B = $(addprefix $(LIBFT_DIR_B), $(LIBFT_FILES_B))

GNL_DIR_B = gnl/
GNL_FILES_B = gnl gnl_utils
GNL_SRCS_B = $(addprefix $(GNL_DIR_B), $(GNL_FILES_B))

PARSE_DIR_B = parsing/
PARSE_FILES_B = parse_file parse_utils parse_textures_verif parse_textures\
				parse_colours parse_map get_map map_line_helper
PARSE_SRCS_B = $(addprefix $(PARSE_DIR_B), $(PARSE_FILES_B))

GAME_DIR_B = game/
GAME_FILES_B = collision door game la_piecette minimap_frame minimap_player minimap_utils\
				minimap mouse move render_utils render
GAME_SRCS_B = $(addprefix $(GAME_DIR_B), $(GAME_FILES_B))

CLEANING_DIR_B = cleaning_and_errors/
CLEANING_FILES_B = cleaning error_msg
CLEANING_SRCS_B = $(addprefix $(CLEANING_DIR_B), $(CLEANING_FILES_B))


SRCS_B = $(FILES_B) $(LIBFT_SRCS_B) $(GNL_SRCS_B) $(PARSE_SRCS_B) $(CLEANING_SRCS_B) $(GAME_SRCS_B)

###########################Objects#########################
OBJS_DIR = objs_and_deps/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS)))
ALL_OBJS = $(addprefix $(OBJS_DIR), \
							$(LIBFT_DIR)\
							$(GNL_DIR)\
							$(PARSE_DIR)\
							$(CLEANING_DIR)\
							$(GAME_DIR))


DEPS = $(patsubst %.o, %.d, $(OBJS))

OBJS_DIR_B = objs_and_deps_bonus/
OBJS_B = $(addprefix $(OBJS_DIR_B), $(addsuffix .o, $(SRCS_B)))
ALL_OBJS_B = $(addprefix $(OBJS_DIR_B), \
							$(LIBFT_DIR_B)\
							$(GNL_DIR_B)\
							$(PARSE_DIR_B)\
							$(CLEANING_DIR_B)\
							$(GAME_DIR_B))


DEPS_B = $(patsubst %.o, %.d, $(OBJS_B))
##########################MiniLibX#########################
MLX_DIR = minilibx/
MLX_LIB = $(MLX_DIR)libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11

##########################Rules############################
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(ALL_OBJS)
	$(C) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_B)%.o: $(SRCS_DIR_B)%.c
	mkdir -p $(ALL_OBJS_B)
	$(C) $(CFLAGS) -c $< -o $@

all: ${NAME}

bonus: ${NAME_BONUS}

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	$(C) $(CFLAGS) $^ -o $@ $(MLX_FLAGS) -lm

$(NAME_BONUS): $(OBJS_B) $(MLX_LIB)
	$(C) $(CFLAGS) $^ -o $@ $(MLX_FLAGS) -lm

clean:
	rm -rf $(OBJS_DIR) $(OBJS_DIR_B)
	@make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS) $(DEPS_B)
