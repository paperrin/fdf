/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:44:41 by paperrin          #+#    #+#             */
/*   Updated: 2017/01/12 19:16:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/include/ft_math.h"

# define W 800
# define H 480

# define KEYCODE_ESCAPE 53

typedef struct	s_mlx
{
	void	*core;
	void	*win;
	char	*draw_buffer;
	void	*db_img;
	int		db_w;
	int		endian;
	int		bits_per_pxl;
}				t_mlx;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_point
{
	t_pos		pos;
	t_color		color;
}				t_point;

typedef struct	s_map
{
	int			w;
	int			h;
	int			**z;
	int			z_max;
	int			z_min;
}				t_map;

unsigned int	get_color(void *mlx_core, t_color color);
void			draw_line(t_mlx *mlx, t_point p1, t_point p2);
t_map			*read_map(char *file_path);
void			draw_map(t_mlx *mlx, t_map *map);
void			set_pixel(t_mlx *mlx, t_point *point);
int				event_expose(void *param);
int				event_key(int keycode, void *param);
void			exit_clean(t_map *map);

#endif
