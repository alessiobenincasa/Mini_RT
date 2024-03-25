/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:05:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/24 12:57:13 by albeninc         ###   ########.fr       */
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

void	render_scene(t_vars *vars)
{
	t_world		world;
	world.object_count = 6;
    world.objects = malloc(sizeof(t_object) * 6);

	t_sphere* floor = malloc(sizeof(t_sphere));
	*floor = sphere();
	floor->transform = scaling(10, 0.01, 10);
	floor->material = material();
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;

	t_sphere* left_wall = malloc(sizeof(t_sphere));
	*left_wall = sphere();
	left_wall->transform = matrix_mult_four(translation(0, 0, 5), rotation_y(-(M_PI / 4)), rotation_x(M_PI / 2), scaling(10, 0.01, 10));
	left_wall->material = floor->material;

	t_sphere* right_wall = malloc(sizeof(t_sphere));
	*right_wall = sphere();
	right_wall->transform = matrix_mult_four(translation(0, 0, 5), rotation_y(M_PI / 4), rotation_x(M_PI / 2), scaling(10, 0.01, 10));
	right_wall->material = floor->material;

	t_sphere* middle = malloc(sizeof(t_sphere));
	*middle = sphere();
	middle->transform = translation(-0.5, 1, 0.5);
	middle->material = material();
	middle->material.color = color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;

	t_sphere* right = malloc(sizeof(t_sphere));
	*right = sphere();
	right->transform = multiply_matrices(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right->material = material();
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;

	t_sphere* left = malloc(sizeof(t_sphere));
	*left = sphere();
	left->transform = multiply_matrices(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left->material = material();
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;

    world.objects[0].data = floor;
    world.objects[1].data = left_wall;
    world.objects[2].data = right_wall;
    world.objects[3].data = middle;
    world.objects[4].data = right;
    world.objects[5].data = left;
	world.light = point_light(point(-10, 10, -10), color(1, 1, 1));

	t_camera	cam;
	cam = camera(WIDTH, HEIGHT, (double)(M_PI / 3));
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	render_mlx(vars, cam, world);
}

t_canvas	render_scene2(void)
{
	t_world		world;
	world.object_count = 6;
    world.objects = malloc(sizeof(t_object) * 6);

	t_sphere* floor = malloc(sizeof(t_sphere));
	*floor = sphere();
	floor->transform = scaling(10, 0.01, 10);
	floor->material = material();
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;

	t_sphere* left_wall = malloc(sizeof(t_sphere));
	*left_wall = sphere();
	left_wall->transform = matrix_mult_four(translation(0, 0, 5), rotation_y(-(M_PI / 4)), rotation_x(M_PI / 2), scaling(10, 0.01, 10));
	left_wall->material = floor->material;

	t_sphere* right_wall = malloc(sizeof(t_sphere));
	*right_wall = sphere();
	right_wall->transform = matrix_mult_four(translation(0, 0, 5), rotation_y(M_PI / 4), rotation_x(M_PI / 2), scaling(10, 0.01, 10));
	right_wall->material = floor->material;

	t_sphere* middle = malloc(sizeof(t_sphere));
	*middle = sphere();
	middle->transform = translation(-0.5, 1, 0.5);
	middle->material = material();
	middle->material.color = color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;

	t_sphere* right = malloc(sizeof(t_sphere));
	*right = sphere();
	right->transform = multiply_matrices(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right->material = material();
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;

	t_sphere* left = malloc(sizeof(t_sphere));
	*left = sphere();
	left->transform = multiply_matrices(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left->material = material();
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;

    world.objects[0].data = floor;
    world.objects[1].data = left_wall;
    world.objects[2].data = right_wall;
    world.objects[3].data = middle;
    world.objects[4].data = right;
    world.objects[5].data = left;
	world.light = point_light(point(-10, 10, -10), color(1, 1, 1));

	t_camera	cam;
	cam = camera(100, 50, (double)(M_PI / 3.0));
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	t_canvas image = render(cam, world);
	return (image);
}
