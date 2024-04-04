/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/04 11:24:52 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_color	mult_clr_sclr(t_color c, float scalar);
t_color	subtract_colors(t_color c1, t_color c2);
t_color	add_colors(t_color c1, t_color c2);
t_color	multiply_colors(t_color color1, t_color color2);

t_color	add_colors(t_color c1, t_color c2)
{
	t_color	total_color;

	total_color.red = c1.red + c2.red;
	total_color.green = c1.green + c2.green;
	total_color.blue = c1.blue + c2.blue;
	return (total_color);
}

t_color	subtract_colors(t_color c1, t_color c2)
{
	t_color	total_color;

	total_color.red = c1.red - c2.red;
	total_color.green = c1.green - c2.green;
	total_color.blue = c1.blue - c2.blue;
	return (total_color);
}

t_color	mult_clr_sclr(t_color c, float scal)
{
	t_color	total_color;

	total_color.red = c.red * scal;
	total_color.green = c.green * scal;
	total_color.blue = c.blue * scal;
	return (total_color);
}

t_color	multiply_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.red = c1.red * c2.red;
	result.green = c1.green * c2.green;
	result.blue = c1.blue * c2.blue;
	return (result);
}

t_color	add_three_colors(t_color one, t_color two, t_color three)
{
	t_color	total_light;

	total_light = color(0, 0, 0);
	total_light = add_colors(total_light, one);
	total_light = add_colors(total_light, two);
	total_light = add_colors(total_light, three);
	total_light = clamp_color(total_light);
	return (total_light);
}
