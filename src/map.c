/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:49:19 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/14 17:39:04 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_point				iso(int x, int y, int z, t_map *map)
{
	t_point		iso;
	double		cm;
	double		scale;
	t_pos		offset;

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
	iso.pos.x = offset.x + round(((double)((map->h * scale) - y) * 0.4) + x);
	iso.pos.y = offset.y + round(y + z);
	return (iso);
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

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (y > 0)
			{
				if (map->z[y][x] > map->z[y - 1][x])
					draw_line(mlx, iso(x, y, map->z[y][x], map), iso(x, y - 1, map->z[y - 1][x], map));
				else
					draw_line(mlx, iso(x, y - 1, map->z[y - 1][x], map), iso(x, y, map->z[y][x], map));
			}
			if (x > 0)
			{
				if (map->z[y][x] > map->z[y][x - 1])
					draw_line(mlx, iso(x, y, map->z[y][x], map), iso(x - 1, y, map->z[y][x - 1], map));
				else
					draw_line(mlx, iso(x - 1, y, map->z[y][x - 1], map), iso(x, y, map->z[y][x], map));
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->core, mlx->win, mlx->db_img, 0, 0);
}
