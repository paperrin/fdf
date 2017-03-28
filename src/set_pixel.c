/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:09:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/28 20:25:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_pixel(t_mlx *mlx, t_point *point)
{
	size_t			index;
	unsigned int 	color;
	int				i;

	color = get_color(mlx->core, point->color);
	index = ((point->pos.y * mlx->db_w) + (point->pos.x * 4));
	i = -1;
	while (++i < 3)
		mlx->draw_buffer[index + i] = color >> (i * 8);
}
