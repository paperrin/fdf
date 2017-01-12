/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:48:16 by paperrin          #+#    #+#             */
/*   Updated: 2017/01/12 19:55:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_matrix	*ft_matrix_new(int size)
{
	t_matrix	*ret;

	ret = (t_matrix*)malloc(sizeof(t_matrix));
	if (ret)
	{
		ret->size = size;
		ret->m = (float*)malloc(sizeof(float) * (size * size));
		if (!ret->m)
			ft_memdel((void**)&ret);
	}
	return (ret);
}

t_matrix	*ft_matrix_to_identity(t_matrix * const mx)
{
	int		i;

	if (mx)
	{
		i = -1;
		while (++i < mx->size * mx->size)
			mx->m[i] = (i % (mx->size + 1) == 0);
	}
	return (mx);
}

void		ft_matrix_del(t_matrix **mx)
{
	if (mx)
	{
		if ((*mx)->m)
			ft_memdel((void**)&(*mx)->m);
		ft_memdel((void**)mx);
	}
}
