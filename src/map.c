/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:49:19 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 19:21:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord				*to_iso_coord(int x, int y, int z)
{
	t_coord		*iso;

	iso = (t_coord*)malloc(sizeof(t_coord));
	if (!iso)
		return (NULL);

	iso->x = W / 2 + 5 * ((x - z) / sqrt(2));
	iso->y = H / 2 + 5 * ((x + 2 * y + z) / sqrt(6));
	return (iso);
}

static t_coord		***alloc_map(char *file_path)
{
	int		ret;
	int		fd;
	char	*line;
	size_t	nb_lines;
	t_coord	***map;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	nb_lines = 0;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
		nb_lines++;
	if (ret != 0)
		return (NULL);
	close(fd);
	map = (t_coord***)malloc(sizeof(t_coord**) * (nb_lines + 1));
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

static t_coord		**line_to_coord_tab(char *line, size_t line_index)
{
	char		**values;
	t_coord		**tab;
	int			i;

	values = ft_strsplit(line, ' ');
	if (!values)
		return (NULL);
	i = 0;
	while (values[i])
		i++;
	tab = (t_coord**)malloc(sizeof(t_coord*) * (i + 1));
	if (!tab)
	{
		free_str_tab(values);
		return (NULL);
	}
	i = -1;
	while (values[++i])
	{
		if (!(tab[i] = to_iso_coord(i, line_index, ft_atoi(values[i]))))
			return (NULL);
	}
	tab[i] = NULL;
	free_str_tab(values);
	return (tab);
}

t_coord 			***read_map(char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		y;
	t_coord	***map;

	if (!(map = alloc_map(file_path)))
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	y = 0;
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		map[y] = line_to_coord_tab(line, y);
		if (!map[y])
		{
			close(fd);
			return (NULL);
		}
		y++;
	}
	map[y] = NULL;
	close(fd);
	return (map);
}

void				draw_map(t_mlx *mlx, t_coord ***map)
{
	t_color	color;
	int		x;
	int		y;

	color.r = 255;
	color.g = 120;
	color.b = 120;
	y = 0;
	while (map[y])
	{
		x = 0;
		ft_putendl("LY");
		while (map[y][x])
		{
			if (x > 0)
				draw_line(mlx, *map[x][y], *map[x - 1][y], &color);
			if (y > 0)
				draw_line(mlx, *map[x][y], *map[x][y - 1], &color);
			x++;
		ft_putendl("LX");
		}
		y++;
	}
	ft_putendl("DONE");
}
