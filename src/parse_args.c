/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 22:56:37 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 01:31:51 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *error)
{
	if (error)
	{
		ft_putstr("error: ");
		ft_putendl(error);
	}
	exit(EXIT_FAILURE);
}

void	usage(char *error)
{
	if (error)
	{
		ft_putstr("error: ");
		ft_putendl(error);
	}
	ft_putstr("usage: ./fdf file [<bottom_color> <top_color>]\n"
	"       ./fdf file [single_color]\n");
	exit(EXIT_FAILURE);
}

int		parse_args(int ac, char **av, t_app *app)
{
	app->filepath = NULL;
	app->custom_colors = 0;
	if (ac >= 2)
	{
		if (!(app->filepath = ft_strdup(av[1])))
			return (0);
		if (ac >= 3)
		{
			if (!ft_atoi_hex_is_valid(av[2])
					|| (ac >= 4 && !ft_atoi_hex_is_valid(av[3])))
				usage("Colors must be in hexadecimal format."
				" (example: 0xffffff)");
			app->custom_colors = 1;
			app->color_bot = ft_atoi_hex(av[2]);
			app->color_top = ft_atoi_hex((ac >= 4) ? av[3] : av[2]);
		}
		else
		{
			app->color_bot = COLOR_BOT_DEFAULT;
			app->color_top = COLOR_TOP_DEFAULT;
		}
	}
	else
		usage("Missing map file.");
	return (1);
}
