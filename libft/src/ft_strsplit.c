/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:08:46 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/12 15:29:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		**alloc_tab(char const *s, char c)
{
	size_t	word_count;
	char	**tab;
	int		i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab = (char**)malloc(sizeof(char*) * (word_count + 1));
	return (tab);
}

static char		**free_tab(char **tab)
{
	int		tab_i;

	tab_i = 0;
	while (tab[tab_i])
		free(tab[tab_i++]);
	free(tab);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	tab_i;
	size_t	i;

	if (!s || !(tab = alloc_tab(s, c)))
		return (NULL);
	tab_i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i == 0)
			break ;
		tab[tab_i] = ft_strsub(s, 0, i);
		if (!tab[tab_i])
			return (free_tab(tab));
		tab_i++;
		s += i;
	}
	tab[tab_i] = NULL;
	return (tab);
}
