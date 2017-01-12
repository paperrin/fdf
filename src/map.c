/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:49:19 by paperrin          #+#    #+#             */
/*   Updated: 2017/01/12 19:58:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point				iso(int x, int y, int z, t_map *map)
{
	t_point		iso;
	double		cm;
	double		scale;
	t_pos		offset;
	t_pos		line_offset;

	scale = (W / (map->w + map->h * 0.4));
	scale = scale < (H / ((map->h / 3) + map->z_max + ABS(map->z_min))) ? scale : (H / ((map->h / 3) + map->z_max + ABS(map->z_min)));
	scale *= 0.8;

	cm = (double)(ABS(map->z_min) + z) / (ABS(map->z_max) + ABS(map->z_min));
	iso.color.r = 0 + cm * 255;
	iso.color.g = 50 + cm * 205;
	iso.color.b = 0 + cm * 255;

	y *= scale / 3;
	x *= scale;
	z *= -scale;
	offset.x = 0;
	offset.y = (double)(map->z_max * scale);
	line_offset.x = (map->h * scale - y) * 0.4;
	iso.pos.x = offset.x + line_offset.x + x;
	iso.pos.y = offset.y + y + z;
	iso.pos.x = round(iso.pos.x);
	iso.pos.y = round(iso.pos.y);
	return (iso);
}

t_point				custom(int x, int y, int z, t_map *map)
{
	t_matrix	*mx;
	t_point		point;
	t_vec3f		map_pos;
	t_vec3f		pos;

	mx = ft_matrix_to_identity(ft_matrix_new(4));
	mx->m[3] = 100;
	mx->m[7] = 150;
	map_pos = ft_vec3f(x * 10, y * 10, z * 10);
	pos = ft_vec3f_transform(&map_pos, mx);
	(void)map;

	point.color.r = 255;
	point.color.g = 255;
	point.color.b = 255;
	point.pos.x = pos.x;
	point.pos.y = pos.y - pos.z;
	point.pos.x = round(point.pos.x);
	point.pos.y = round(point.pos.y);
	return (point);
}

static t_map		*alloc_map(char *file_path)
{
	int		ret;
	int		fd;
	char	*line;
	size_t	nb_lines;
	t_map	*map;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	nb_lines = 0;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
		nb_lines++;
	if (ret != 0)
		return (NULL);
	close(fd);
	map->w = -1;
	map->h = nb_lines;
	map->z = (int**)malloc(sizeof(int*) * (nb_lines));
	map->z_max = 0;
	map->z_min = 0;
	if (!map->z)
		ft_memdel((void**)&map);
	return (map);
}

static void			free_str_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static t_map		*line_to_map(char *line, size_t line_index, t_map *map)
{
	char		**values;
	int			i;
	int			z;

	values = ft_strsplit(line, ' ');
	if (!values)
		return (NULL);
	i = 0;
	while (values[i])
		i++;
	if (map->w == -1)
		map->w = i;
	else if (map->w != i)
		return (NULL);
	map->z[line_index] = (int*)malloc(sizeof(int) * i);
	if (!map->z[line_index])
	{
		free_str_tab(values);
		return (NULL);
	}
	i = -1;
	while (values[++i])
	{
		z = ft_atoi(values[i]);
		map->z[line_index][i] = z;
		if (z > map->z_max)
			map->z_max = z;
		else if (z < map->z_min)
			map->z_min = z;
	}
	free_str_tab(values);
	return (map);
}

t_map 				*read_map(char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		y;
	t_map	*map;

	if (!(map = alloc_map(file_path)))
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	y = 0;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (!line_to_map(line, y, map))
		{
			close(fd);
			return (NULL);
		}
		y++;
	}
	close(fd);
	return (map);
}

void				draw_map(t_mlx *mlx, t_map *map)
{
	int		x;
	int		y;
	t_point (*f_proj)(int, int, int, t_map*);

	f_proj = &custom;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (y > 0)
			{
				if (map->z[y][x] > map->z[y - 1][x])
					draw_line(mlx, (*f_proj)(x, y, map->z[y][x], map), (*f_proj)(x, y - 1, map->z[y - 1][x], map));
				else
					draw_line(mlx, (*f_proj)(x, y - 1, map->z[y - 1][x], map), (*f_proj)(x, y, map->z[y][x], map));
			}
			if (x > 0)
			{
				if (map->z[y][x] > map->z[y][x - 1])
					draw_line(mlx, (*f_proj)(x, y, map->z[y][x], map), (*f_proj)(x - 1, y, map->z[y][x - 1], map));
				else
					draw_line(mlx, (*f_proj)(x - 1, y, map->z[y][x - 1], map), (*f_proj)(x, y, map->z[y][x], map));
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->core, mlx->win, mlx->db_img, 0, 0);
}
