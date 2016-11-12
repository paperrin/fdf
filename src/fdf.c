/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:00 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 11:34:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>
#define W 400
#define H 400

void	draw(t_mlx *mlx)
{
	t_color		color;
	t_coord		p1;
	t_coord		p2;

	// v
	color.r = 255;
	color.g = 120;
	color.b = 120;

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 4 * 3, .y = H};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 4, .y = H};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 4 * 3, .y = 0};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 4, .y = 0};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 2, .y = 0};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W / 2, .y = H};
	put_line(mlx, p1, p2, &color);

	// h
	color.r = 120;
	color.g = 120;
	color.b = 255;

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W, .y = (H / 4) * 3};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y =	H / 2};
	p2 = (t_coord){.x = W, .y = H / 4};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = 0, .y = H / 4 * 3};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = 0, .y = H / 4};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = 0, .y = H / 2};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W, .y = H / 2};
	put_line(mlx, p1, p2, &color);

	// d
	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W, .y = 0};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = 0, .y = H};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = W, .y = H};
	put_line(mlx, p1, p2, &color);

	p1 = (t_coord){.x = W / 2, .y = H / 2};
	p2 = (t_coord){.x = 0, .y = 0};
	put_line(mlx, p1, p2, &color);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;

	(void)ac;
	(void)av;
	mlx.core = mlx_init();
	mlx.win = mlx_new_window(mlx.core, W, H, "FDF paperrin");
	draw(&mlx);
	mlx_loop(mlx.core);
	return (0);
}
