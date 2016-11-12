/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:33:17 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:37:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	ret = (char*)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (ret)
	{
		ret = ft_strcpy(ret, s1);
		ft_strcpy(ret + s1_len, s2);
	}
	return (ret);
}
