/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:09:55 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 23:18:13 by paperrin         ###   ########.fr       */
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

void	key_escape(t_app *app, char *e)
{
	(void)e;
	destroy_app(app, EXIT_SUCCESS);
}

void	key_move(t_app *app, char *e)
{
	if (*e == 'U')
		app->map->y_off++;
	else if (*e == 'D')
		app->map->y_off--;
	else if (*e == 'L')
		app->map->x_off++;
	else if (*e == 'R')
		app->map->x_off--;
	else if (*e == '+')
		app->map->zoom *= 2;
	else if (*e == '-' && app->map->zoom > 1)
		app->map->zoom /= 2;
	update_matrices(app->map);
	draw_map(app);
}

void	key_rot(t_app *app, char *e)
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

int		event_key_down(int kc, void *param)
{
	static const int			nb_keys = 13;
	static void const *const	handlers[(nb_keys + 1) * 3] = {
		(void*)KC_ESCAPE, &key_escape, (void*)"X",
		(void*)KC_UP, &key_move, (void*)"U",
		(void*)KC_DOWN, &key_move, (void*)"D",
		(void*)KC_LEFT, &key_move, (void*)"L",
		(void*)KC_RIGHT, &key_move, (void*)"R",
		(void*)KC_ZOOM_P, &key_move, (void*)"+",
		(void*)KC_ZOOM_M, &key_move, (void*)"-",
		(void*)KC_ROT_X_P, &key_rot, (void*)"X+",
		(void*)KC_ROT_X_M, &key_rot, (void*)"X-",
		(void*)KC_ROT_Y_P, &key_rot, (void*)"Y+",
		(void*)KC_ROT_Y_M, &key_rot, (void*)"Y-",
		(void*)KC_ROT_Z_P, &key_rot, (void*)"Z+",
		(void*)KC_ROT_Z_M, &key_rot, (void*)"Z-", NULL, NULL, NULL
	};
	int							i;

	i = 0;
	while (handlers[i + 1] && kc != (int)handlers[i])
		i += 3;
	if (handlers[i + 1])
		((void (*)(t_app*, char*))handlers[i + 1])
			((t_app*)param, (char*)handlers[i + 2]);
	return (0);
}
