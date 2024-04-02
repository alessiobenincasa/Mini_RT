/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/02 11:22:35 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_canvas	canvas(int width, int height);
void		write_pixel(t_canvas *c, int x, int y, t_color color);

t_canvas	canvas(int width, int height)
{
	t_canvas	c;
	int			i;

	i = 0;
	c.width = width;
	c.height = height;
	c.pixels = (t_color *)ft_calloc(width * height, sizeof(t_color));
	while (i < width * height)
	{
		c.pixels[i] = (t_color){0, 0, 0};
		i++;
	}
	return (c);
}

void	write_pixel(t_canvas *c, int x, int y, t_color color)
{
	if (x >= 0 && x < c->width && y >= 0 && y < c->height)
	{
		c->pixels[y * c->width + x] = color;
	}
}
