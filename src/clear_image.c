/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 20:37:13 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/01 20:52:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			clear_image(t_mlx_image *image, unsigned int color)
{
	int				i;
	int				j;

	j = -1;
	while (++j * 4 < image->bytes_width * image->bytes_height)
	{
		i = -1;
		while (++i < 3)
			image->pixels[j * 4 + i] = color >> (i * 8);
	}
}
