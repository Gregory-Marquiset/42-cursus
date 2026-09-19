/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:04:17 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/17 05:52:47 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_line
{
	int				x;
	int				start;
	int				end;
	unsigned int	color;
}	t_line;

typedef struct s_dda
{
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		side;
}	t_dda;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
}	t_ray;

typedef struct s_triangle
{
	double			ax;
	double			ay;
	double			bx;
	double			by;
	double			cx;
	double			cy;
	int				offset_x;
	int				offset_y;
	int				center_x;
	int				center_y;
	int				minx;
	int				maxx;
	int				miny;
	int				maxy;
	unsigned int	color;
}	t_triangle;

typedef enum e_id
{
	NO,
	SO,
	WE,
	EA
}	t_id;

typedef struct s_parse
{
	int			id;
	int			len_max;
	int			numb_of_line;
	int			map_start;
	int			last_map_line;
	int			player;
	int			n_col;
	int			n_text;
	char		*north_text_path;
	char		*south_text_path;
	char		*west_text_path;
	char		*east_text_path;
	char		*door_text_path;
}	t_parse;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_dtw_helper
{
	int				y;
	int				tex_x;
	int				tex_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int	color;
	double			step;
	double			tex_pos;
	double			wallx;
	char			*texel;
	char			*dst;
	t_img			*tex;
}	t_dtw_helper;

typedef struct s_cub
{
	int				cam;
	char			**map;
	int				*floor_colour;
	unsigned int	floor;
	int				*ceiling_colour;
	unsigned int	ceil;
	int				*win_height;
	int				*win_width;
	void			*north_text;
	void			*south_text;
	void			*west_text;
	void			*east_text;
	void			*door_text;
	void			*mlx_ptr;
	void			*win_ptr;
	t_parse			*parse;
	t_player		player;
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	t_img			tex_north;
	t_img			tex_south;
	t_img			tex_east;
	t_img			tex_west;
	t_img			tex_door;
	int				center_x;
	int				center_y;
	unsigned int	frame_color;
	t_img			coin_frames[8];
	int				current_coin_frame;
	double			last_coin_update;
}	t_cub;

#endif
