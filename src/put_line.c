/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:55 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 11:44:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_line(t_mlx *mlx, t_coord p1, t_coord p2, t_color *color)
{
	t_coord		diff;
	t_coord		step;
	int			err;

	diff.x = ABS((p2.x - p1.x));
	diff.y = ABS((p2.y - p1.y));
	step.x = (p1.x < p2.x ? 1 : -1);
	step.y = (p1.y < p2.y ? 1 : -1);
	err = (diff.x > diff.y ? diff.x : -diff.y) / 2;
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
