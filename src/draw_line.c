/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:11:36 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/28 20:25:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_color	color_gradient(t_point a, t_point b, t_pos cur, t_pos diff)
{
	t_color		color;
	float		max;
	float		state;

	max = diff.x + diff.y;
	diff.x = ABS((cur.x - b.pos.x));
	diff.y = ABS((cur.y - b.pos.y));
	state = 1 - ((diff.x + diff.y) / max);
	color.r = a.color.r + ( (b.color.r - a.color.r) * state );
	color.g = a.color.g + ( (b.color.g - a.color.g) * state );
	color.b = a.color.b + ( (b.color.b - a.color.b) * state );
	return (color);
}

static int		line_out_of_screen(t_pos const * const pos
		, t_pos const * const step)
{
	if ((pos->x < 0 && step->x == -1)
		|| (pos->x >= W && step->x == 1)
		|| (pos->y < 0 && step->y == -1)
		|| (pos->y >= H && step->y == 1))
		return (1);
	return (0);
}

static int		pixel_in_screen(t_pos *pos)
{
	return (pos->x >= 0 && pos->x < W && pos->y >= 0 && pos->y < H);
}

void	draw_line(t_mlx *mlx, t_point a, t_point b)
{
	t_pos		diff;
	t_pos		step;
	int			err;
	t_point		cur;

	diff.x = ABS((b.pos.x - a.pos.x));
	diff.y = ABS((b.pos.y - a.pos.y));
	step.x = (a.pos.x < b.pos.x ? 1 : -1);
	step.y = (a.pos.y < b.pos.y ? 1 : -1);
	err = (diff.x > diff.y ? diff.x : -diff.y) / 2.0;
	cur.pos.x = a.pos.x;
	cur.pos.y = a.pos.y;
	while (1)
	{
		if (pixel_in_screen((&cur.pos)))
		{
			cur.color = color_gradient(a, b, cur.pos, diff);
			set_pixel(mlx, &cur);
		}
		else if (line_out_of_screen((&cur.pos), &step))
			return ;
		if (
			((step.x == 1) ? cur.pos.x >= b.pos.x : 1)
			&& ((step.x == -1) ? cur.pos.x <= b.pos.x : 1)
			&& ((step.y == 1) ? cur.pos.y >= b.pos.y : 1)
			&& ((step.y == -1) ? cur.pos.y <= b.pos.y : 1))
			break ;
		if (err > -diff.x)
		{
			err -= diff.y;
			cur.pos.x += step.x;
		}
		if (err < diff.y)
		{
			err += diff.x;
			cur.pos.y += step.y;
		}
	}
}
