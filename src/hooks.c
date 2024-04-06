/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:28:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:15:24 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix_registry	g_matrix_registry;

int	handle_close(t_vars *vars)
{
	free_scene_data(vars->scene);
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	vars->img.img_ptr = NULL;
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	vars->mlx = NULL;
	for (size_t i = 0; i < g_matrix_registry.count; i++)
	{
		free(g_matrix_registry.matrices[i].elements);
	}
	free(g_matrix_registry.matrices);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		handle_close(vars);
	return (0);
}
