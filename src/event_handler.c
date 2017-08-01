/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:09:55 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 21:04:16 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		event_expose(void *param)
{
	t_app	*app;

	app = (t_app*)param;
	mlx_put_image_to_window(app->mlx.core, app->mlx.win
			, app->draw_buf.image, 0, 0);
	return (0);
}

void	key_escape(t_app *app, char e)
{
	(void)e;
	exit_clean(app->map);
}

void	key_move(t_app *app, char e)
{
	if (e == 'U')
		app->map->yOff++;
	else if (e == 'D')
		app->map->yOff--;
	else if (e == 'L')
		app->map->xOff++;
	else if (e == 'R')
		app->map->xOff--;
	update_matrices(app->map);
	draw_map(app);
}

void	key_rot_x(t_app *app, char e)
{
	if (e == '+')
		app->map->xRot += ROT_STEP;
	else if (e == '-')
		app->map->xRot -= ROT_STEP;
	if (app->map->xRot >= 360)
		app->map->xRot -= 360;
	else if (app->map->xRot < 0)
		app->map->xRot += 360;
	update_matrices(app->map);
	draw_map(app);
}

void	key_rot_y(t_app *app, char e)
{
	if (e == '+')
		app->map->yRot += ROT_STEP;
	else if (e == '-')
		app->map->yRot -= ROT_STEP;
	if (app->map->yRot >= 360)
		app->map->yRot -= 360;
	else if (app->map->yRot < 0)
		app->map->yRot += 360;
	update_matrices(app->map);
	draw_map(app);
}

void	key_rot_z(t_app *app, char e)
{
	if (e == '+')
		app->map->zRot += ROT_STEP;
	else if (e == '-')
		app->map->zRot -= ROT_STEP;
	if (app->map->zRot >= 360)
		app->map->zRot -= 360;
	else if (app->map->zRot < 0)
		app->map->zRot += 360;
	update_matrices(app->map);
	draw_map(app);
}

void	key_zoom(t_app *app, char e)
{
	if (e == '+')
		app->map->zoom *= 2;
	else if (e == '-' && app->map->zoom > 1)
		app->map->zoom /= 2;
	update_matrices(app->map);
	draw_map(app);
}

int		event_key_down(int kc, void *param)
{
	static const int	nb_keys = 13;
	static void const	* const handlers[(nb_keys + 1) * 3] = {
		(void*)KC_ESCAPE, &key_escape, (void*)'X',
		(void*)KC_UP, &key_move, (void*)'U',
		(void*)KC_DOWN, &key_move, (void*)'D',
		(void*)KC_LEFT, &key_move, (void*)'L',
		(void*)KC_RIGHT, &key_move, (void*)'R',
		(void*)KC_ROT_X_P, &key_rot_x, (void*)'+',
		(void*)KC_ROT_X_M, &key_rot_x, (void*)'-',
		(void*)KC_ROT_Y_P, &key_rot_y, (void*)'+',
		(void*)KC_ROT_Y_M, &key_rot_y, (void*)'-',
		(void*)KC_ROT_Z_P, &key_rot_z, (void*)'+',
		(void*)KC_ROT_Z_M, &key_rot_z, (void*)'-',
		(void*)KC_ZOOM_P, &key_zoom, (void*)'+',
		(void*)KC_ZOOM_M, &key_zoom, (void*)'-',

		NULL, NULL, NULL
	};
	int					i;
	void 				(*f_key)(t_app*, char);

	i = 0;
	while (handlers[i + 1] && kc != (int)handlers[i])
		i += 3;
	if (handlers[i + 1])
	{
		f_key = handlers[i + 1];
		(*f_key)((t_app*)param, (char)handlers[i + 2]);
	}
	return (0);
}
