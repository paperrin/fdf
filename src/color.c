/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 13:41:46 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/11 14:00:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_color(t_color *color)
{
	int		encoded;

	encoded = 0;
	encoded |= color->b;
	encoded |= color->g << 8;
	encoded |= color->r << 16;
	return (encoded);
}
