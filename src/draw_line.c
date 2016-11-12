/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:55 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 19:23:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
void	draw_line(t_mlx *mlx, t_coord p1, t_coord p2, t_color *color)
{
	t_coord		diff;
	t_coord		step;
	int			err;

	p1.x = round(p1.x);
	p1.y = round(p1.y);
	p2.x = round(p2.x);
	p2.y = round(p2.y);
	printf("[{.x = %f, .y = %f}{.x = %f, .y = %f}]\n", p1.x, p1.y, p2.x, p2.y);
	diff.x = ABS((p2.x - p1.x));
	diff.y = ABS((p2.y - p1.y));
	step.x = (p1.x < p2.x ? 1 : -1);
	step.y = (p1.y < p2.y ? 1 : -1);
	err = (diff.x > diff.y ? diff.x : -diff.y) / 2.0;
	while (1)
	{
		mlx_pixel_put(mlx->core, mlx->win, p1.x, p1.y, get_color(color));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		if (err > -diff.x)
		{
			err -= diff.y;
			p1.x += step.x;
		}
		if (err < diff.y)
		{
			err += diff.x;
			p1.y += step.y;
		}
	}
}
