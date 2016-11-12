/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:11:40 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:28:11 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *dst;

	dst = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (dst)
		dst = ft_strcpy(dst, s1);
	return (dst);
}
