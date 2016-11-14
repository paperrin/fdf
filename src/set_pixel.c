/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:09:00 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/14 14:54:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		in_screen(t_pos *pos)
{
	return (pos->x >= 0 && pos->x < W && pos->y >= 0 && pos->y < H);
}

void			set_pixel(t_mlx *mlx, t_point *point)
{
	size_t			index;
	unsigned int 	color;
	int				i;

	if (!in_screen(&point->pos))
		return ;
	color = get_color(mlx->core, point->color);
	index = ((point->pos.y * mlx->db_w) + (point->pos.x * 4));
	i = -1;
	while (++i < 3)
		mlx->draw_buffer[index + i] = color >> (i * 8);
}
