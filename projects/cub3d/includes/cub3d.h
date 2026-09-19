/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:40:48 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 04:21:07 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "msg.h"
# include "gnl.h"
# include "struct.h"
# include "../minilibx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>

# define PXL 64200000
# define NAME "Cub3D"

/********************FT_FROM_LIBFT********************/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strndup(char **dup, char *s, int n);
int		ft_split(char ***dest, char *s, char *c);
char	*ft_strchr(const char *s, int c);
int		ft_n_mot(char const *s, char *c);
long	ft_atol(const char *str);
char	*ft_strnstr(const char *big, const char *little, size_t len);

/********************PARSING********************/
/*Get_map.c*/
int		ft_get_map(t_cub *cub, int fd);

/*Map_line_helper,c*/
void	ft_complete_map(t_cub *cub, int i, int *index);
void	ft_set_player_dir(t_cub *cub, char direction);
void	ft_set_player_position(t_cub *cub, int i, int index, char direction);
void	ft_handle_tab(t_cub *cub, int *i, int index);
void	ft_fill_map_char(t_cub *cub, char c, int i, int index);

/*Parse_colours.c*/
int		ft_is_colours(t_cub *cub, char *line);

/*Parse_file.c*/
int		ft_parse_file(t_cub *cub, char *filename);

/*Parse_map.c*/
int		ft_is_mapline(t_cub *cub, char *line, int n);

/*Parse_texture_verif.c*/
int		ft_is_identifier(t_parse *parse, char *line);
int		ft_is_texture(t_parse *parse, char *line);

/*Parse_texture.c*/
int		ft_set_textures(t_cub *cub);

/*Parse_utils.c*/
int		ft_is_whitespace(char c);
int		ft_is_charset(char *cset, char c);

/********************CLEANING********************/
/*Cleaning.c*/
int		free_all(t_cub *cub);
void	free_parse_struct(t_cub *cub);
void	ft_destroy_tab(char ***output);

/*Error_msg.c*/
void	ft_err_str(char *err_msg);
void	ft_err_2str(char *err_msg1, char *err_msg2);

/********************GAME********************/
/*Collision.c*/
void	cb_collision(t_cub *cub, double newx, double newy);

/*Door.c*/
void	cb_toggle_door(t_cub *cub);

/*Game.c*/
int		cb_set_and_display_game(t_cub *cub);

/*La_piecette.c*/
void	cb_update_coin_frame(t_cub *cub);

/*Minimap_frame.c*/
void	cb_draw_minimap_frame(t_cub *cub, int offset_x, int offset_y, int size);

/*Minimap_player.c*/
void	cb_draw_player_on_minimap_fixed(t_cub *cub);

/*Minimap_utils.c*/
void	cb_pixel_put_minimap(t_cub *cub, int x, int y, unsigned int color);
void	cb_fill_triangle_pixels(t_cub *cub, t_triangle *triangle);

/*Minimap.c*/
void	cb_draw_minimap_fixed(t_cub *cub);

/*Mouse.c*/
int		cb_mouse_move(int x, int y, t_cub *cub);

/*Move.c*/
void	cb_move_forward(t_cub *cub);
void	cb_move_backward(t_cub *cub);
void	cb_move_left(t_cub *cub);
void	cb_move_right(t_cub *cub);

/*Render_utils.c*/
int		cb_perform_dda(t_cub *cub, t_dda *d);
void	cb_init_dda(t_dda *d, t_cub *cub, t_ray *r);
void	cb_compute_line_dimensions(t_cub *cub, t_ray *r, t_dda *d);
void	cb_draw_floor_ceiling(t_cub *cub, int x, int start, int end);
t_img	*cb_select_texture(t_cub *cub, t_dda *d, t_ray *r);

/*Render.c*/
int		cb_render_frame(t_cub *cub);

#endif
