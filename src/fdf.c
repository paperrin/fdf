/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:43:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 22:08:04 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		create_app(t_app *app, size_t width, size_t height
		, char *title)
{
	app->width = width;
	app->height = height;
	if (!(app->mlx.core = mlx_init()))
		return (0);
	if (!(app->mlx.win = mlx_new_window(app->mlx.core
					, width, height, title)))
		return (0);
	if (!(app->draw_buf.image = mlx_new_image(app->mlx.core, width, height)))
		destroy_app(app, EXIT_FAILURE);
	app->draw_buf.pixels = mlx_get_data_addr(
			app->draw_buf.image
			, &(app->draw_buf.bits_per_pixel)
			, &(app->draw_buf.bytes_width)
			, &(app->draw_buf.is_big_endian));
	app->draw_buf.bytes_height = height;
	return (1);
}

void			destroy_app(t_app *app, int exit_code)
{
	mlx_destroy_window(app->mlx.core, app->mlx.win);
	if (app->draw_buf.image)
		mlx_destroy_image(app->mlx.core, app->draw_buf.image);
	exit(exit_code);
}

void			exit_clean(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->h)
		free(map->z[i]);
	free(map);
	exit(EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	t_app		app;

	app.map = NULL;
	if (ac == 2)
		app.map = read_map(av[1]);
	if (!app.map)
		exit_clean(app.map);
	if (!create_app(&app, W, H, "FDF paperrin"))
		return (EXIT_FAILURE);
	app.map->zoom = 1;
	app.map->x_off = 0;
	app.map->y_off = 0;
	app.map->x_rot = 0;
	app.map->y_rot = 0;
	app.map->z_rot = 0;
	mlx_expose_hook(app.mlx.win, &event_expose, app.mlx.core);
	mlx_hook(app.mlx.win, 2, 3, &event_key_down, &app);
	update_matrices(app.map);
	draw_map(&app);
	mlx_loop(app.mlx.core);
	return (EXIT_SUCCESS);
}
