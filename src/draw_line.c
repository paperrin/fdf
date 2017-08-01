/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:11:36 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 22:08:13 by paperrin         ###   ########.fr       */
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
	color.r = a.color.r + ((b.color.r - a.color.r) * state);
	color.g = a.color.g + ((b.color.g - a.color.g) * state);
	color.b = a.color.b + ((b.color.b - a.color.b) * state);
	return (color);
}

static int		line_out_of_screen(t_pos const *const pos
		, t_pos const *const step)
{
	if ((pos->x < 0 && step->x == -1) || (pos->x >= W && step->x == 1)
		|| (pos->y < 0 && step->y == -1) || (pos->y >= H && step->y == 1))
		return (1);
	return (0);
}

static void		do_step(t_pos diff, t_point *cur
		, int *err, t_pos step)
{
	if (*err > -diff.x)
	{
		*err -= diff.y;
		(*cur).pos.x += step.x;
	}
	if (*err < diff.y)
	{
		*err += diff.x;
		(*cur).pos.y += step.y;
	}
}

static int		is_end_of_line(t_pos step, t_pos cur, t_pos end)
{
	return (
		((step.x == 1) ? cur.x >= end.x : 1)
		&& ((step.x == -1) ? cur.x <= end.x : 1)
		&& ((step.y == 1) ? cur.y >= end.y : 1)
		&& ((step.y == -1) ? cur.y <= end.y : 1));
}

void			draw_line(t_app *app, t_point a, t_point b)
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
	cur.pos = (t_pos){a.pos.x, a.pos.y};
	while (1)
	{
		if (line_out_of_screen((&cur.pos), &step))
			return ;
		else if (cur.pos.x >= 0 && cur.pos.x < W
				&& cur.pos.y >= 0 && cur.pos.y < H)
		{
			cur.color = color_gradient(a, b, cur.pos, diff);
			set_pixel(app, &cur);
		}
		if (is_end_of_line(step, cur.pos, b.pos))
			break ;
		do_step(diff, &cur, &err, step);
	}
}
