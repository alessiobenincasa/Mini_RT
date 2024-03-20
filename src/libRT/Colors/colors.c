/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:09 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/19 15:31:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	color(float red, float green, float blue)
{
	t_color	c;

	c.red = red;
	c.green = green;
	c.blue = blue;
	return (c);
}

t_color pixel_at(t_canvas c, int x, int y)
{
    if (x >= 0 && x < c.width && y >= 0 && y < c.height)
        return c.pixels[y * c.width + x];
    return (t_color){0, 0, 0};
}
