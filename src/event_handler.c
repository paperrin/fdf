/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:09:55 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/28 19:41:49 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		event_expose(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	mlx_put_image_to_window(mlx->core, mlx->win, mlx->db_img, 0, 0);
	return (0);
}

void	key_escape(t_map *map, char e)
{
	(void)e;
	exit_clean(map);
}

void	key_move(t_map *map, char e)
{
	if (e == 'U')
		map->yOff++;
	else if (e == 'D')
		map->yOff--;
	else if (e == 'L')
		map->xOff++;
	else if (e == 'R')
		map->xOff--;
	draw_map(map->mlx, map);
}

void	key_rot_x(t_map *map, char e)
{
	if (e == '+')
		map->xRot += ROT_STEP;
	else if (e == '-')
		map->xRot -= ROT_STEP;
	if (map->xRot >= 360)
		map->xRot -= 360;
	else if (map->xRot < 0)
		map->xRot += 360;
	draw_map(map->mlx, map);
}

void	key_rot_y(t_map *map, char e)
{
	if (e == '+')
		map->yRot += ROT_STEP;
	else if (e == '-')
		map->yRot -= ROT_STEP;
	if (map->yRot >= 360)
		map->yRot -= 360;
	else if (map->yRot < 0)
		map->yRot += 360;
	draw_map(map->mlx, map);
}

void	key_rot_z(t_map *map, char e)
{
	if (e == '+')
		map->zRot += ROT_STEP;
	else if (e == '-')
		map->zRot -= ROT_STEP;
	if (map->zRot >= 360)
		map->zRot -= 360;
	else if (map->zRot < 0)
		map->zRot += 360;
	draw_map(map->mlx, map);
}

void	key_zoom(t_map *map, char e)
{
	if (e == '+')
		map->zoom *= 2;
	else if (e == '-' && map->zoom > 1)
		map->zoom /= 2;
	draw_map(map->mlx, map);
}

int		event_key(int kc, void *param)
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
	void 				(*f_key)(t_map*, char);

	i = 0;
	while (handlers[i + 1] && kc != (int)handlers[i])
		i += 3;
	if (handlers[i + 1])
	{
		f_key = handlers[i + 1];
		(*f_key)((t_map*)param, (char)handlers[i + 2]);
	}
	return (0);
}
