/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:45:03 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	color(float red, float green, float blue);
t_color	pixel_at(t_canvas c, int x, int y);
int		convert_color_to_int(t_color color);
void	set_color(t_color *color, float red, float green, float blue);

t_color	color(float red, float green, float blue)
{
	t_color	c;

	c.red = red;
	c.green = green;
	c.blue = blue;
	return (c);
}

t_color	pixel_at(t_canvas c, int x, int y)
{
	if (x >= 0 && x < c.width && y >= 0 && y < c.height)
		return (c.pixels[y * c.width + x]);
	return ((t_color){0, 0, 0});
}

int	convert_color_to_int(t_color color)
{
	int	red;
	int	green;
	int	blue;
	int	combined_color;

	red = (int)(color.red * 255);
	green = (int)(color.green * 255);
	blue = (int)(color.blue * 255);
	red = red < 0 ? 0 : (red > 255 ? 255 : red);
	green = green < 0 ? 0 : (green > 255 ? 255 : green);
	blue = blue < 0 ? 0 : (blue > 255 ? 255 : blue);
	combined_color = (red << 16) | (green << 8) | blue;
	return (combined_color);
}

void	set_color(t_color *color, float red, float green, float blue)
{
	color->red = red;
	color->green = green;
	color->blue = blue;
}
