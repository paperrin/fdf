/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/06 18:54:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_clean(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->h)
		free(map->z[i]);
	free(map);
	exit(EXIT_SUCCESS);
}

void	init_matrices(t_map *map)
{
	(void)map;
}

int		main(int ac, char **av)
{
	t_mlx		mlx;
	t_map		*map;

	map = NULL;
	if (ac == 2)
		map = read_map(av[1]);
	if (!map)
		exit_clean(map);
	mlx.core = mlx_init();
	mlx.db_img = mlx_new_image(mlx.core, W, H);
	mlx.draw_buffer = mlx_get_data_addr(mlx.db_img, &mlx.bits_per_pxl
			, &mlx.db_w, &mlx.endian);
	mlx.win = mlx_new_window(mlx.core, W, H, "FDF paperrin");
	mlx_expose_hook(mlx.win, &event_expose, (void*)&mlx);
	mlx_key_hook(mlx.win, &event_key, map);
	draw_map(&mlx, map);
	mlx_loop(mlx.core);
	return (0);
}
