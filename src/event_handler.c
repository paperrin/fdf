/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:09:55 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/03 23:28:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				event_expose(void *param)
{
	t_app	*app;

	app = (t_app*)param;
	mlx_put_image_to_window(app->mlx.core, app->mlx.win
			, app->draw_buf.image, 0, 0);
	put_info(app);
	return (0);
}

static void		call_key_function(int kc, t_app *app, void *handlers[])
{
	int				i;

	i = 0;
	while (handlers[i + 1] && kc != (int)handlers[i])
		i += 3;
	if ((int)handlers[i + 1])
		((void (*)(t_app*, char*))handlers[i + 1])
			(app, (char*)handlers[i + 2]);
}

int				event_key_down(int kc, void *param)
{
	static const int			nb_keys = 16;
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
		(void*)KC_ROT_Z_M, &key_rot, (void*)"Z-",
		(void*)KC_RESET, &key_reset, (void*)"",
		(void*)KC_TOGGLE_DEBUG, &key_toggle_info, (void*)"D",
		(void*)KC_TOGGLE_CONTROLS, &key_toggle_info, (void*)"C",
		NULL, NULL, NULL};

	call_key_function(kc, (t_app*)param, (void*)handlers);
	return (0);
}
