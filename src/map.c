/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:49:19 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/27 17:01:32 by paperrin         ###   ########.fr       */
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
