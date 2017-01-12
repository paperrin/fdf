/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:34:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/01/12 17:41:05 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

static float	cross_multiply(float *line, int line_size, float *col, int col_size)
{
	float	ret;
	int		size;
	int		i;

	ret = 0;
	size = (line_size < col_size ? line_size : col_size);
	i = -1;
	while (++i < size)
		ret += line[i] * col[i * col_size];
	return (ret);
}

void			ft_matrix_multiply(
		t_matrix *dest, t_matrix const * const a, t_matrix const * const b)
{
	int		line;
	int		col;
	int		size;

	if (!(dest && dest->m && a && a->m && b && b->m))
		return;
	size = (a->size < b->size ? a->size : b->size);
	line = -1;
	while (++line < size)
	{
		col = -1;
		while (++col < size)
		{
			dest->m[col + line * size] = cross_multiply(
					&a->m[line * a->size], a->size
					, &b->m[col], b->size
			);
		}
	}
}
