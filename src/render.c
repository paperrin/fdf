/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 18:01:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/03 22:42:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point			proj(int x, int y, int z, t_map *map)
{
	t_point		point;
	t_vec3f		map_pos;
	t_vec3f		pos;

	map_pos = ft_vec3f(x, y, z);
	point.color = get_point_color(&map_pos, map);
	pos = ft_vec3f_transform(&map_pos, &map->mx);
	point.pos.x = roundf(pos.x);
	point.pos.y = roundf(pos.y);
	return (point);
}

static void				draw_sides(t_app *app, int x, int y)
{
	if (y > 0)
	{
		if (app->map->z[y][x] > app->map->z[y - 1][x])
			draw_line(app, proj(x, y, app->map->z[y][x], app->map)
					, proj(x, y - 1, app->map->z[y - 1][x], app->map));
		else
			draw_line(app, proj(x, y - 1, app->map->z[y - 1][x], app->map)
					, proj(x, y, app->map->z[y][x], app->map));
	}
	if (x > 0)
	{
		if (app->map->z[y][x] > app->map->z[y][x - 1])
			draw_line(app, proj(x, y, app->map->z[y][x], app->map)
					, proj(x - 1, y, app->map->z[y][x - 1], app->map));
		else
			draw_line(app, proj(x - 1, y, app->map->z[y][x - 1], app->map)
					, proj(x, y, app->map->z[y][x], app->map));
	}
}

void					draw_map(t_app *app)
{
	int			x;
	int			y;

	clear_image(&app->draw_buf, get_color(app->mlx.core, (t_color){0, 0, 0}));
	y = 0;
	while (y < app->map->h)
	{
		x = 0;
		while (x < app->map->w)
		{
			draw_sides(app, x, y);
			x++;
		}
		y++;
	}
	mlx_clear_window(app->mlx.core, app->mlx.win);
	mlx_put_image_to_window(app->mlx.core, app->mlx.win
			, app->draw_buf.image, 0, 0);
	put_info(app);
}
