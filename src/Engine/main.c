/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/26 13:35:00 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void render_sphere(t_vars *vars)
{
    int x = 0; 
    int y = 0;
    int canvas_pixel = 1200;
    double wall_size = 0.5;
    double pixel_size = wall_size / canvas_pixel;
    double wall_z = -4.5;
    double half = wall_size / 2.0;
    
	t_world		world;
	world.object_count = 4;
    world.objects = malloc(sizeof(t_object) * world.object_count);

    t_sphere* floor = malloc(sizeof(t_sphere));
	*floor = sphere();
	floor->transform = scaling(10, 0.01, 10);
    floor->center = point(0, -125, 0);
	floor->material = material();
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;

	t_sphere* right = malloc(sizeof(t_sphere));
	*right = sphere();
	right->transform = scaling(0.5, 0.5, 0.5);
    right->center = point(3.5, 2, 0);
	right->material = material();
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
    
	t_sphere* middle = malloc(sizeof(t_sphere));
	*middle = sphere();
	// middle->transform = translation(-0.5, 1, 0.5);
    middle->center = point(0, -0.5, 0);
	middle->material = material();
	middle->material.color = color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;

    t_sphere* left = malloc(sizeof(t_sphere));
	*left = sphere();
    left->center = point(-4, -1, -3);
	left->transform = scaling(0.33, 0.33, 0.33);
	left->material = material();
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;

    
    
    world.objects[0].data = middle;
    world.objects[1].data = right;
    world.objects[2].data = left;
    world.objects[3].data = floor;
	world.light = point_light(point(-10, 10, -10), color(1, 1, 1));

    while (y < canvas_pixel)
    {
        double world_y = half - pixel_size * y - (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
        x = 0;
        while (x < canvas_pixel)
        {
            double world_x = -half + pixel_size * x + (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
            t_tuple pixel_position = {world_x, world_y, wall_z, 1};
            t_tuple ray_direction = normalize(subtract_tuples(pixel_position, (t_tuple){0, 0, -5, 1}));
            t_ray r = ray((t_tuple){0, 0, -5, 1}, ray_direction);

			t_color color = color_at(world, r);
			int final_color = convert_color_to_int(color);
			my_mlx_pixel_put(vars, x, y, final_color);
            x++;
        }
        y++;
    }
}

void	print_shapes(t_vars *vars, t_scene_data *scene_data)
{
	t_list	*current;

    (void)vars;
	current = scene_data->shapes;
	while (current)
	{
        if (current->type == SPHERE)
            print_sphere((t_sphere *)current->content);
        else if (current->type == PLANE)
            print_plane((t_plane *)current->content);
        else if (current->type == CYLINDER)
            print_cylinder((t_cylinder *)current->content);
		current = current->next;
	}
}


int	main(int ac, char **av)
{
    t_vars          vars;
	t_scene_data	scene_data;

	if (init_data(&scene_data, ac, av) == NULL)
		return (1);
	printf("shape count : %d\n", scene_data.shape_count);
    print_shapes(&vars, &scene_data);

    // vars.mlx = mlx_init();
    // vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniLibX - Sphere Rendering");
    // vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    // vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length,
    //                                  &vars.img.endian);

    // render_sphere(&vars);

    // mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    // mlx_loop(vars.mlx);
    free_scene_data(&scene_data);
    return (0);
}
