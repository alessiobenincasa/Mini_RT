/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/26 14:48:10 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_shapes(t_list *list)
{
	t_list	*current;

	current = list;
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

void transfer_scene_data_to_world(t_scene_data *scene, t_world *world)
{
    world->objects = scene->shapes;
    world->object_count = scene->shape_count;

    printf("\nWorlds objects:\n");
    print_shapes(world->objects);
    if (scene->light) 
    {
        world->light = *(scene->light);
        printf("\nWorlds Light:\n");
        print_light(&world->light);
    }
}

void render_sphere(t_vars *vars, t_scene_data *scene)
{
    int x = 0; 
    int y = 0;
    int canvas_pixel = 1200;
    double wall_size = 0.5;
    double pixel_size = wall_size / canvas_pixel;
    double wall_z = -4.5;
    double half = wall_size / 2.0;
    
	t_world		world;
    transfer_scene_data_to_world(scene, &world);

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



int	main(int ac, char **av)
{
    t_vars          vars;
	t_scene_data	scene_data;

	if (init_data(&scene_data, ac, av) == NULL)
		return (1);
	printf("shape count : %d\n", scene_data.shape_count);
    // print_shapes(&vars, &scene_data->shapes);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniLibX - Sphere Rendering");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length,
                                     &vars.img.endian);

    render_sphere(&vars, &scene_data);

    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);
    free_scene_data(&scene_data);
    return (0);
}
