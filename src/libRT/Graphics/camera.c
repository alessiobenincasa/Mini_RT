/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:05:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/26 13:58:07 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	double world_y = camera.half_height + yoffset;

	t_tuple	pixel = multiply_matrix_tuple(inverse(camera.transform), point(world_x, world_y, -1));
	t_tuple	origin = multiply_matrix_tuple(inverse(camera.transform), point(0, 0, -5));
	t_tuple	direction = normalize(subtract_tuples(pixel, origin));

	return (ray(origin, direction));
}

t_canvas	render(t_camera cam, t_world w)
{
	t_canvas	image = canvas(cam.hsize, cam.vsize);
	
	for (int y = 0; y <= cam.vsize; y++)
	{
		for (int x = 0; x <= cam.hsize; x++)
		{
			t_ray r = ray_for_pixel(cam, x, y);
			t_color color = color_at(w, r);
			write_pixel(&image, x, y, color);
		}
	}
	return (image);
}

void		render_mlx(t_vars *vars, t_camera cam, t_world w)
{
    double wall_size = 0.3;
    double half = wall_size / 2.0;
    double wall_z = 100;
    double pixel_size = wall_size / 1200;


	for (int y = 0; y < cam.vsize; y++)
	{
		double world_y = half - pixel_size * y - (wall_size / 2.0 - cam.vsize / 2.0 * pixel_size);
		for (int x = 0; x < cam.hsize; x++)
		{
			double world_x = -half + pixel_size * x + (wall_size / 2.0 - cam.hsize / 2.0 * pixel_size);
			if (x % 500 < 1)
				printf("WORLD: x = %f, y = %f, z = %f\n", world_x, world_y, wall_z);
            t_tuple pixel_position = {world_x, world_y, wall_z, 1};
            t_tuple ray_direction = normalize(subtract_tuples(pixel_position, (t_tuple){0, 0, -5, 1}));
            t_ray r = ray((t_tuple){0, 0, -5, 1}, ray_direction);
			t_color color = color_at(w, r);
			int final_color = convert_color_to_int(color);
			my_mlx_pixel_put(vars, x, y, final_color);
		}
	}
}

t_matrix	matrix_mult_four(t_matrix one, t_matrix two, t_matrix three, t_matrix four)
{
	t_matrix result = multiply_matrices(multiply_matrices(multiply_matrices(one, two), three), four);
	return (result);
}
