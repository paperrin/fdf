/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:00 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/13 12:45:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int		main(int ac, char **av)
{
	t_mlx		mlx;
	t_map		*map;
	//t_color		color = {.r = 255, .g = 120, .b = 120};

	map = NULL;
	if (ac == 2)
		map = read_map(av[1]);
	if (!map)
		return (EXIT_FAILURE);
	mlx.core = mlx_init();
	mlx.win = mlx_new_window(mlx.core, W, H, "FDF paperrin");
	//draw_line(&mlx, *to_iso_coord(0, 0, 0), *to_iso_coord(1, 0, 0), &color);
	//draw_line(&mlx, *to_iso_coord(1, 0, 0), *to_iso_coord(1, 1, 0), &color);
	//draw_line(&mlx, *to_iso_coord(1, 1, 0), *to_iso_coord(0, 1, 0), &color);
	//draw_line(&mlx, *to_iso_coord(0, 1, 0), *to_iso_coord(0, 0, 0), &color);
	draw_map(&mlx, map);
	mlx_loop(mlx.core);
	return (0);
}
