/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:59:15 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:39:30 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		nb_char_len(int n)
{
	int		len;

	len = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	if (n < 0)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	char	*ret;
	int		len;
	long	nb;

	nb = n;
	nb = ABS(nb);
	len = nb_char_len(n);
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	len = len ? len - 1 : len;
	while (nb > 9)
	{
		ret[len] = '0' + nb % 10;
		nb /= 10;
		len--;
	}
	ret[len] = '0' + nb;
	len--;
	if (len == 0)
		ret[len] = '-';
	return (ret);
}
