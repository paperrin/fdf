/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:00 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/14 14:50:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int		main(int ac, char **av)
{
	t_mlx		mlx;
	t_map		*map;

	map = NULL;
	if (ac == 2)
		map = read_map(av[1]);
	if (!map)
		return (EXIT_FAILURE);
	mlx.core = mlx_init();
	mlx.db_img = mlx_new_image(mlx.core, W, H);
	mlx.draw_buffer = mlx_get_data_addr(mlx.db_img, &mlx.bits_per_pxl
			, &mlx.db_w, &mlx.endian);
	printf("%d\n", mlx.db_w);
	mlx.win = mlx_new_window(mlx.core, W, H, "FDF paperrin");
	draw_map(&mlx, map);
	mlx_loop(mlx.core);
	return (0);
}
