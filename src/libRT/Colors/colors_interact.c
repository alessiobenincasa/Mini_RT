/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_color	hadarmard_product(t_color c, t_color b);
t_color	multiply_color_scalar(t_color c, float scalar);
t_color	subtract_colors(t_color c1, t_color c2);
t_color	add_colors(t_color c1, t_color c2);
t_color	multiply_colors(t_color color1, t_color color2);

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

t_color	multiply_colors(t_color color1, t_color color2)
{
	t_color	result;

	result.red = color1.red * color2.red;
	result.green = color1.green * color2.green;
	result.blue = color1.blue * color2.blue;
	return (result);
}
