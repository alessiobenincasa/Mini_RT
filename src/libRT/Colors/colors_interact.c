/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:31:10 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/19 15:31:37 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	add_colors(t_color c1, t_color c2)
{
	return (color(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue));
}

t_color	subtract_colors(t_color c1, t_color c2)
{
	return (color(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue));
}

t_color	multiply_color_scalar(t_color c, float scalar)
{
	return (color(c.red * scalar, c.green * scalar, c.blue * scalar));
}

t_color	hadarmard_product(t_color c, t_color b)
{
	return (color(c.red * b.red, c.green * b.green, c.blue * b.blue));
}
