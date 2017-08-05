/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 19:03:25 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/05 21:55:35 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	get_color_component(t_vec3f const *const pos
		, t_map const *const map
		, unsigned char bot, unsigned char top)
{
	int		min;
	int		max;

	min = (pos->z < 0) ? map->z_min : 0;
	max = (pos->z < 0) ? 0 : map->z_max;
	if (map->z_max - map->z_min == 0)
		return ((pos->z < 0) ? bot : top);
	return (
		bot + ((float)(pos->z - map->z_min) / (map->z_max - map->z_min))
			* (top - bot));
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

static t_color			get_color_for_gradient(t_vec3f const *const pos
		, t_map const *const map, int is_land)
{
	t_color		color;

	if (is_land)
	{
		color.r = get_color_component(pos, map, 0, 255);
		color.g = get_color_component(pos, map, 100, 255);
		color.b = get_color_component(pos, map, 0, 255);
	}
	else
	{
		color = (t_color){50, 50, 200};
		color.r = get_color_component(pos, map, 50, 0);
		color.g = get_color_component(pos, map, 50, 10);
		color.b = get_color_component(pos, map, 100, 255);
	}
	return (color);
}

t_color					get_point_color(t_vec3f const *const pos
		, t_map const *const map)
{
	t_color		color;
	int			raw;

	if (map->is_colored)
	{
		raw = map->colors[(int)pos->y][(int)pos->x];
		color.r = (0xff0000 & raw) >> 16;
		color.g = (0x00ff00 & raw) >> 8;
		color.b = (0x0000ff & raw) >> 0;
	}
	else
		color = get_color_for_gradient(pos, map, pos->z > 0);
	return (color);
}
