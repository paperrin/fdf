/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:09:55 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/21 14:28:31 by paperrin         ###   ########.fr       */
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

int		event_key(int keycode, void *param)
{
	if (keycode == KEYCODE_ESCAPE)
		exit_clean(param);
	return (0);
}
