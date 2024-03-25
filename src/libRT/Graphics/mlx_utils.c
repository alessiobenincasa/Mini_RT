/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 11:37:59 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (!(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT))
	{
		dst = vars->img.addr + (y * vars->img.line_length + \
		x * (vars->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
