/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:28:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 13:28:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	handle_close(t_vars *vars)
{
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
    free_scene_data(vars->scene);
	exit(EXIT_SUCCESS);
}

int key_hook(int keycode, t_vars *vars)
{
    if (keycode == XK_Escape)
        handle_close(vars);
    return (0);
}
