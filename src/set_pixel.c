/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:09:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 20:48:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_pixel(t_app *app, t_point *point)
{
	size_t			index;
	unsigned int 	color;
	int				i;

	color = get_color(app->mlx.core, point->color);
	index = ((point->pos.y * app->draw_buf.bytes_width) + (point->pos.x * 4));
	i = -1;
	while (++i < 3)
		app->draw_buf.pixels[index + i] = color >> (i * 8);
}
