/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:38:45 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 00:07:33 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	screen_dimensions(t_point a, t_vars *vars)
{
	int	x;
	int	y;

	if (vars->max_z - vars->min_z > 90)
		vars->z_modify = 9;
	if (vars->max_z - vars->min_z > 900)
		vars->z_modify = 90;
	a = isometric_projection(a, vars);
	x = a.x;
	y = a.y;
	if (x < vars->screen.min_x && x < 0)
		vars->screen.min_x = x;
	if (y < vars->screen.min_y && y < 0)
		vars->screen.min_y = y;
	if (!vars->screen.max_x || x > vars->screen.max_x)
		vars->screen.max_x = x;
	if (!vars->screen.max_y || y > vars->screen.max_y)
		vars->screen.max_y = y;
}

void	map_to_point(t_vars *vars)
{
	int	x;
	int	y;

	vars->point_map = malloc(sizeof(t_point *) * vars->nb_lines);
	y = -1;
	while (vars->map[++y])
	{
		x = 0;
		vars->point_map[y] = malloc(sizeof(t_point) * vars->nb_cols);
		while (x < vars->nb_cols)
		{	
			(vars->point_map)[y][x] = init_point(x, y, vars->map[y][x]);
			screen_dimensions((vars->point_map)[y][x], vars);
			x++;
		}
	}
}
