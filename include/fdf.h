/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:44:41 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 11:33:12 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include "mlx.h"

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
	int		x;
	int		y;
}				t_coord;

int		get_color(t_color *color);
void	put_line(t_mlx *mlx, t_coord p1, t_coord p2, t_color *color);

#endif
