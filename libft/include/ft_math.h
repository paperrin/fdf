/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:17:25 by paperrin          #+#    #+#             */
/*   Updated: 2017/01/12 19:01:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "libft.h"

typedef struct	s_vec3f
{
	float x;
	float y;
	float z;
}				t_vec3f;

typedef struct	s_matrix
{
	int		size;
	float	*m;
}				t_matrix;

t_matrix	*ft_matrix_new(int size);
void		ft_matrix_del(t_matrix **mx);
t_matrix	*ft_matrix_to_identity(t_matrix * const mx);
void		ft_matrix_multiply(
		t_matrix *dest
		, t_matrix const * const a
		, t_matrix const * const b
);

t_vec3f		ft_vec3f(float x, float y, float z);
t_vec3f		*ft_vec3f_new(float x, float y, float z);
t_vec3f		ft_vec3f_transform(
		t_vec3f const * const vec
		, t_matrix const * const mx
);

#endif
