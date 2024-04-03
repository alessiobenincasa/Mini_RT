/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:05:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:08:29 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_camera	camera(int hsize, int vsize, double fov)
{
	t_camera c;
	
	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
	c.transform = identity_matrix();

	double	half_view = tan(c.fov / 2.0);
	double	aspect = (double)c.hsize / (double)c.vsize;

	if (aspect >= 1.0)
	{
		c.half_width = half_view;
		c.half_height = (half_view / aspect);
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	
	c.pixel_size = (c.half_width * 2.0) / (double)(c.hsize);
	return (c);
}

t_ray	ray_for_pixel(t_camera camera, int px, int py)
{
	double xoffset = ((double)(px) + 0.5) * camera.pixel_size;
	double yoffset = ((double)(py) + 0.5) * camera.pixel_size;

	double world_x = camera.half_width - xoffset;
	double world_y = camera.half_height - yoffset;

	t_tuple	pixel = multiply_matrix_tuple(inverse(camera.transform), point(world_x, world_y, -1));
	t_tuple	origin = multiply_matrix_tuple(inverse(camera.transform), point(0, 0, 0));
	t_tuple	direction = normalize(subtract_tuples(pixel, origin));

	return (ray(origin, direction));
}

t_matrix	matrix_mult_four(t_matrix one, t_matrix two, t_matrix three, t_matrix four)
{
	t_matrix result = multiply_matrices(multiply_matrices(multiply_matrices(one, two), three), four);
	return (result);
}
