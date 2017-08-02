/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:44:41 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/02 20:00:38 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/include/ft_math.h"

# define W 1600
# define H 800

# define ROT_STEP 15

# define KC_ESCAPE 53

# define KC_ZOOM_M 27
# define KC_ZOOM_P 24

# define KC_UP 126
# define KC_DOWN 125
# define KC_LEFT 123
# define KC_RIGHT 124

# define KC_ROT_X_P 13
# define KC_ROT_X_M 1
# define KC_ROT_Z_P 14
# define KC_ROT_Z_M 12
# define KC_ROT_Y_P 2
# define KC_ROT_Y_M 0

typedef struct		s_map
{
	t_matrix		mx;
	t_matrix		mx_ortho;
	t_matrix		mx_proj;
	int				w;
	int				h;
	int				**z;
	int				is_colored;
	int				**colors;
	int				z_max;
	int				z_min;
	int				zoom;
	int				x_off;
	int				y_off;
	int				x_rot;
	int				y_rot;
	int				z_rot;
}					t_map;

typedef struct		s_mlx_image
{
	void			*image;
	char			*pixels;
	int				bits_per_pixel;
	int				bytes_width;
	int				bytes_height;
	int				is_big_endian;
}					t_mlx_image;

typedef struct		s_mlx
{
	void			*core;
	void			*win;
}					t_mlx;

typedef struct		s_app
{
	t_mlx			mlx;
	t_mlx_image		draw_buf;
	int				width;
	int				height;
	t_map			*map;
}					t_app;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_pos
{
	float			x;
	float			y;
}					t_pos;

typedef struct		s_point
{
	t_pos			pos;
	t_color			color;
}					t_point;

void				destroy_app(t_app *app, int exit_code);
void				clear_image(t_mlx_image *image, unsigned int color);
unsigned int		get_color(void *mlx_core, t_color color);
void				draw_line(t_app *app, t_point p1, t_point p2);
void				update_matrices(t_map *map);
t_map				*read_map(char *file_path);
void				draw_map(t_app *app);
int					**alloc_colors(t_map *map);
int					get_map_color(t_map *map, const char *str);
t_color				get_point_color(t_vec3f const *const pos
		, t_map const *const map);
void				set_pixel(t_app *app, t_point *point);
int					event_expose(void *param);
int					event_key_down(int keycode, void *param);

#endif
