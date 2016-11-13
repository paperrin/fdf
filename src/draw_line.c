/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:55 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/13 15:28:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_color	color_gradient(t_point a, t_point b, t_pos cur, t_pos diff)
{
	t_color		color;
	double		delta;
	double		state;

	delta = diff.x + diff.y;
	diff.x = ABS((b.pos.x - cur.x));
	diff.y = ABS((b.pos.y - cur.y));
	state = diff.x + diff.y;
	color.r = b.color.r + ( (ABS((b.color.r - a.color.r))) / delta * state);
	color.g = b.color.g + ( (ABS((b.color.g - a.color.g))) / delta * state);
	color.b = b.color.b + ( (ABS((b.color.b - a.color.b))) / delta * state);
	return (color);
}

void	draw_line(t_mlx *mlx, t_point a, t_point b)
{
	t_pos		diff;
	t_pos		step;
	int			err;
	t_pos		cur;

	diff.x = ABS((b.pos.x - a.pos.x));
	diff.y = ABS((b.pos.y - a.pos.y));
	step.x = (a.pos.x < b.pos.x ? 1 : -1);
	step.y = (a.pos.y < b.pos.y ? 1 : -1);
	err = (diff.x > diff.y ? diff.x : -diff.y) / 2.0;
	cur.x = a.pos.x;
	cur.y = a.pos.y;
	while (1)
	{
		mlx_pixel_put(mlx->core, mlx->win, cur.x, cur.y, get_color(color_gradient(a, b, cur, diff)));
		if (cur.x == b.pos.x && cur.y == b.pos.y)
			break ;
		if (err > -diff.x)
		{
			err -= diff.y;
			cur.x += step.x;
		}
		if (err < diff.y)
		{
			err += diff.x;
			cur.y += step.y;
		}
	}
}
