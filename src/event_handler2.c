/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 23:25:12 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/03 23:25:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		key_escape(t_app *app, char *e)
{
	(void)e;
	destroy_app(app, EXIT_SUCCESS);
}

void		key_reset(t_app *app, char *e)
{
	(void)e;
	app->map->x_off = 0;
	app->map->y_off = 0;
	app->map->zoom = 1;
	app->map->x_rot = 0;
	app->map->y_rot = 0;
	app->map->z_rot = 0;
	update_matrices(app->map);
	draw_map(app);
}

void		key_move(t_app *app, char *e)
{
	if (*e == 'U')
		app->map->y_off++;
	else if (*e == 'D')
		app->map->y_off--;
	else if (*e == 'L')
		app->map->x_off++;
	else if (*e == 'R')
		app->map->x_off--;
	else if (*e == '+' && app->map->zoom < 2048)
		app->map->zoom *= 2;
	else if (*e == '-' && app->map->zoom > 1)
		app->map->zoom /= 2;
	update_matrices(app->map);
	draw_map(app);
}

void		key_rot(t_app *app, char *e)
{
	int		*rot;

	rot = NULL;
	if (*e == 'X')
		rot = &app->map->x_rot;
	else if (*e == 'Y')
		rot = &app->map->y_rot;
	else if (*e == 'Z')
		rot = &app->map->z_rot;
	if (!rot)
		return ;
	if (e[1] == '+')
		*rot += ROT_STEP;
	else if (e[1] == '-')
		*rot -= ROT_STEP;
	if (*rot >= 360)
		*rot -= 360;
	else if (*rot < 0)
		*rot += 360;
	update_matrices(app->map);
	draw_map(app);
}

void		key_toggle_info(t_app *app, char *e)
{
	if (*e == 'D')
		app->show_debug = !app->show_debug;
	else if (*e == 'C')
		app->show_controls = !app->show_controls;
	event_expose(app);
}
