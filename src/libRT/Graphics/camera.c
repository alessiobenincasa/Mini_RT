/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:05:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 09:08:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_camera	camera(int hsize, int vsize, double fov)
{
	t_camera	c;
	double		half_view;
	double		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
	c.transform = identity_matrix();
	half_view = tan(c.fov / 2.0);
	aspect = (double)c.hsize / (double)c.vsize;
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

typedef struct s_xy
{
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;
}			t_xy;

t_xy	xy_init(t_camera camera, int px, int py)
{
	t_xy	data;
	double	xoffset;
	double	yoffset;

	xoffset = ((double)(px) + 0.5) * camera.pixel_size;
	yoffset = ((double)(py) + 0.5) * camera.pixel_size;
	data.world_x = camera.half_width - xoffset;
	data.world_y = camera.half_width - yoffset;
	return (data);
}

t_ray	ray_for_pixel(t_camera camera, int px, int py)
{
	t_xy	data;
	t_ray	r;

	data = xy_init(camera, px, py);
	data.pixel = mult_mat_tup(inverse(camera.transform), point(data.world_x,
				data.world_y, -1));
	data.origin = mult_mat_tup(inverse(camera.transform), point(0, 0, 0));
	data.direction = normalize(subtract_tuples(data.pixel, data.origin));
	r = ray(data.origin, data.direction);
	return (r);
}

t_camera	prepare_camera(t_camera *cam)
{
	t_camera	new_cam;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;

	from = point(cam->position.x, cam->position.y, cam->position.z);
	to = point(0, 0, fabs(cam->position.z - 1));
	up = vector(cam->orientation.x, cam->orientation.y, cam->orientation.z);
	print_camera_direction(from, to, up);
	new_cam = camera(WIDTH, HEIGHT, cam->fov * (M_PI / 180.0));
	new_cam.transform = view_transform(from, to, up);
	return (new_cam);
}

t_matrix	matrix_mult_four(t_matrix one, t_matrix two, t_matrix three,
		t_matrix four)
{
	t_matrix	result;

	result = multiply_matrices(multiply_matrices(multiply_matrices(one, two),
				three), four);
	return (result);
}
