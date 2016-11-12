/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:44:41 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 18:47:42 by paperrin         ###   ########.fr       */
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

# define W 840
# define H 480

typedef struct	s_mlx
{
	void	*core;
	void	*win;
}				t_mlx;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

int				get_color(t_color *color);
void			draw_line(t_mlx *mlx, t_coord p1, t_coord p2, t_color *color);
t_coord			***read_map(char *file_path);
void			draw_map(t_mlx *mlx, t_coord ***map);
t_coord				*to_iso_coord(int x, int y, int z);

#endif
