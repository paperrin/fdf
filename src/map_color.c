/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 19:03:25 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 00:32:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	get_color_component(t_vec3f const *const pos
		, t_map const *const map
		, unsigned char bot, unsigned char top)
{
	if (map->z_max - map->z_min == 0)
		return (top);
	return (
		bot + ((float)(pos->z - map->z_min) / (map->z_max - map->z_min))
			* (top - bot));
}

static t_color			get_rgb_from_hex(int hex)
{
	t_color		rgb;

	rgb.r = (0xff0000 & hex) >> 16;
	rgb.g = (0x00ff00 & hex) >> 8;
	rgb.b = (0x0000ff & hex) >> 0;
	return (rgb);
}

int						**alloc_colors(t_map *map)
{
	int		**colors;

	colors = (int**)malloc(sizeof(int*) * (map->h));
	map->is_colored = 0;
	return (colors);
}

int						get_map_color(t_map *map, const char *str)
{
	char	*p;

	p = (char*)str;
	while (*p && *p != ',')
		p++;
	if (*p == ',')
		map->is_colored = 1;
	if (ft_strnequ(p, ",0x", 3))
		return (ft_atoi_base(p + 3, 16));
	return (0);
}

t_color					get_point_color(t_vec3f const *const pos
		, t_app const *const app)
{
	t_color		color;
	t_color		color_bot;
	t_color		color_top;
	int			raw;

	if (!app->custom_colors && app->map->is_colored)
	{
		raw = app->map->colors[(int)pos->y][(int)pos->x];
		color = get_rgb_from_hex(raw);
	}
	else
	{
		color_bot = get_rgb_from_hex(app->color_bot);
		color_top = get_rgb_from_hex(app->color_top);
		color.r = get_color_component(pos, app->map, color_bot.r, color_top.r);
		color.g = get_color_component(pos, app->map, color_bot.g, color_top.g);
		color.b = get_color_component(pos, app->map, color_bot.b, color_top.b);
	}
	return (color);
}
