/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:49:19 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 01:30:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map		*alloc_map(char *file_path)
{
	int		ret;
	int		fd;
	char	*line;
	size_t	nb_lines;
	t_map	*map;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		usage("Could not open file.");
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	nb_lines = 0;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
		nb_lines++;
	if (ret != 0)
		error("Could not read file.");
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

static void			*free_str_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

static void			set_map_values(t_map *map, char **values
		, size_t line_index)
{
	int		i;
	int		z_value;

	i = -1;
	while (values[++i])
	{
		z_value = ft_atoi(values[i]);
		map->z[line_index][i] = z_value;
		if (z_value > map->z_max)
			map->z_max = z_value;
		else if (z_value < map->z_min)
			map->z_min = z_value;
		map->colors[line_index][i] = get_map_color(map, values[i]);
	}
}

static t_map		*line_to_map(char *line, size_t line_index, t_map *map)
{
	char		**values;
	int			i;

	values = ft_strsplit(line, ' ');
	if (!values)
		return (NULL);
	i = 0;
	while (values[i])
		i++;
	if (map->w == -1)
		map->w = i;
	else if (map->w != i)
		error("Inconsistent map width.");
	map->z[line_index] = (int*)malloc(sizeof(int) * i);
	map->colors[line_index] = (int*)malloc(sizeof(int) * i);
	if (!map->z[line_index] || !map->colors[line_index])
		return (free_str_tab(values));
	set_map_values(map, values, line_index);
	free_str_tab(values);
	return (map);
}

t_map				*read_map(char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		y;
	t_map	*map;

	if (!(map = alloc_map(file_path))
			|| !(map->colors = alloc_colors(map)))
		return (NULL);
	if ((fd = open(file_path, O_RDONLY)) < 0)
		usage("Could not open file.");
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
	if (ret != 0)
		error("Could not read file.");
	close(fd);
	return (map);
}
