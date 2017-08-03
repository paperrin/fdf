/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 21:21:26 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/04 00:18:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		put_string_to_screen(t_app *app, t_point point, char *str)
{
	char	**str_lines;
	int		line_nb;

	if (!(str_lines = ft_strsplit(str, '\n')))
		return ;
	line_nb = -1;
	while (str_lines[++line_nb])
	{
		mlx_string_put(app->mlx.core, app->mlx.win
				, point.pos.x, point.pos.y + line_nb * 16
				, get_color(app->mlx.core, point.color)
				, str_lines[line_nb]);
	}
	ft_strsplit_free(str_lines);
}

static char		*get_debug_string(int should_print)
{
	if (!should_print)
		return ("<F1> DEBUG\n");
	else
		return (
		"<F1> DEBUG ------------------------\n \n"
		" x: %5d; y: %5d; zoom: %5d\n"
		" rx: %4d; ry: %4d; rz: %4d\n"
		" colored_map: %s\n \n \n");
}

static char		*get_controls_string(int should_print)
{
	if (!should_print)
		return ("<F2> CONTROLS");
	else
		return (
		"<F2> CONTROLS ---------------------\n \n"
		" Move: <UP> <DOWN> <LEFT> <RIGHT>\n"
		" Rotate arround axis:\n"
		"   x: W & S | y: A & D | z: Q & E\n"
		" Zoom: + & -\n"
		" Reset view: R\n"
		" Quit: <ESC>");
}

void			put_info(t_app *app)
{
	t_point		point;
	char		*str;
	char		*format;
	t_map		*map;

	format = ft_strjoin(get_debug_string(app->show_debug)
			, get_controls_string(app->show_controls));
	if (!format)
		return ;
	map = app->map;
	ft_asprintf(&str, format
			, map->x_off, map->y_off, map->zoom
			, map->x_rot, map->y_rot, map->z_rot
			, (map->is_colored ? "true" : "false"));
	free(format);
	if (!str)
		return ;
	point.pos = (t_pos){5, 0};
	point.color = (t_color){255, 255, 255};
	put_string_to_screen(app, point, str);
	free(str);
}
