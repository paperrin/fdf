/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_matrices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 20:56:01 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 21:00:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		update_matrices(t_map *map)
{
	ft_matrix_to_identity(&map->mx_ortho);
	ft_matrix_translate(&map->mx_ortho, W / 2, H / 2, 0);

	ft_matrix_to_identity(&map->mx_proj);
	ft_matrix_scale(&map->mx_proj, map->zoom, map->zoom, map->zoom);
	ft_matrix_rot_x(&map->mx_proj, MATH_TO_RAD(map->xRot));
	ft_matrix_rot_y(&map->mx_proj, MATH_TO_RAD(map->yRot));
	ft_matrix_rot_z(&map->mx_proj, MATH_TO_RAD(map->zRot));
	ft_matrix_translate(&map->mx_proj, -(map->w / 2) - map->xOff
			, -(map->h / 2) - map->yOff, -((map->z_max - map->z_min) / 2));

	ft_matrix_to_identity(&map->mx);
	ft_matrix_multiply(&map->mx, &map->mx_ortho, &map->mx_proj);
}
