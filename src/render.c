/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 18:01:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/27 20:29:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

static unsigned char	get_color_component(t_vec3f const * const pos
		, t_map const * const map
		, unsigned char bot, unsigned char top)
{
	return (
		bot + ((float)(pos->z - map->z_min)  / (map->z_max - map->z_min))
			* (top - bot)
	);
}

static t_point			proj(int x, int y, int z, t_map *map)
{
	t_matrix	mx;
	t_matrix	mx_ortho;
	t_matrix	mx_proj;

	t_point		point;
	t_vec3f		map_pos;
	t_vec3f		pos;

	int zoom = 20;

	ft_matrix_to_identity(&mx_ortho);
	ft_matrix_scale(&mx_ortho, zoom, zoom, zoom);
	ft_matrix_translate(&mx_ortho, W / 2, H / 2, 0);

	ft_matrix_to_identity(&mx_proj);
	ft_matrix_translate(&mx_proj, -(map->w / 2), -(map->h / 2), -((map->z_max - map->z_min) / 2));
	ft_matrix_rot_x(&mx_proj, MATH_TO_RAD(30));
	ft_matrix_rot_z(&mx_proj, MATH_TO_RAD(30));

	map_pos = ft_vec3f(x, y, z);
	point.color.r = get_color_component(&map_pos, map, 0, 255);
	point.color.g = get_color_component(&map_pos, map, 100, 255);
	point.color.b = get_color_component(&map_pos, map, 0, 255);

	ft_matrix_to_identity(&mx);
	ft_matrix_multiply(&mx, &mx_ortho, &mx_proj);

	pos = ft_vec3f_transform(&map_pos, &mx);
	point.pos.x = roundf(pos.x);
	point.pos.y = roundf(pos.y);
	return (point);
}

static void				draw_sides(t_mlx *mlx, t_map *map, int x, int y)
{
	if (y > 0)
	{
		if (map->z[y][x] > map->z[y - 1][x])
			draw_line(mlx, proj(x, y, map->z[y][x], map)
					, proj(x, y - 1, map->z[y - 1][x], map));
		else
			draw_line(mlx, proj(x, y - 1, map->z[y - 1][x], map)
					, proj(x, y, map->z[y][x], map));
	}
	if (x > 0)
	{
		if (map->z[y][x] > map->z[y][x - 1])
			draw_line(mlx, proj(x, y, map->z[y][x], map)
					, proj(x - 1, y, map->z[y][x - 1], map));
		else
			draw_line(mlx, proj(x - 1, y, map->z[y][x - 1], map)
					, proj(x, y, map->z[y][x], map));
	}
}

// TODO: REMOVE
void					draw_ln(t_mlx *mlx, int x1, int y1, int x2, int y2)
{
	t_point		a;
	a.pos.x = 150 + x1;
	a.pos.y = 150 + y1;
	a.color.r = 0;
	a.color.g = 255;
	a.color.b = 0;

	t_point		b;
	b.pos.x = 150 + x2;
	b.pos.y = 150 + y2;
	b.color.r = 255;
	b.color.g = 0;
	b.color.b = 0;

	draw_line(mlx, a, b);
}

void					draw_map(t_mlx *mlx, t_map *map)
{
	//*/
	int		x;
	int		y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			draw_sides(mlx, map, x, y);
			x++;
		}
		y++;
	}
	//*/

	/*/
	(void)map;

	draw_ln(mlx, 0, 0, 200, 0);
	draw_ln(mlx, 200, 10, 0, 10);
	//*/

	mlx_put_image_to_window(mlx->core, mlx->win, mlx->db_img, 0, 0);
}
