/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/29 14:08:17 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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
        else if (current->type == CONE)
            print_cone((t_cone *)current->content);
		current = current->next;
	}
}

void transfer_scene_data_to_world(t_scene_data *scene, t_world *world)
{
    world->objects = scene->shapes;
    world->object_count = scene->shape_count;
    world->extra_lights = scene->extra_lights;

    printf("\nWorlds objects:\n");
    print_shapes(world->objects);
    if (scene->ambient_light)
    {
        printf("\nAmbient Light\n");
        print_ambient(scene->ambient_light);
    }
    if (scene->light)
    {
        world->light = *(scene->light);
        printf("\nWorlds Light:\n");
        print_light(&world->light);
    }
    if (world->extra_lights)
    {
        t_list	*current = world->extra_lights;
        while (current)
        {
            print_light((t_light *)current->content);
            current = current->next;
        }
    }
}

t_camera    prepare_camera(t_camera *cam)
{	
	t_camera new_cam;

	t_tuple from = point(cam->position.x, cam->position.y, cam->position.z);
    t_tuple to = point(0, 0, fabs(cam->position.z - 1));
    t_tuple up = vector(cam->orientation.x, cam->orientation.y, cam->orientation.z);
	print_camera_direction(from, to, up);

    new_cam = camera(WIDTH, HEIGHT, cam->fov * (M_PI / 180.0));
	new_cam.transform = view_transform(from, to, up);

	return (new_cam);
}

void    render_scene(t_vars *vars, t_scene_data *scene)
{
    int x = 0; 
    int y = 0;

	t_world		world;
    transfer_scene_data_to_world(scene, &world);
    
    t_camera cam = prepare_camera(scene->camera);
    
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            t_ray r = ray_for_pixel(cam, x, y);
			t_color color = color_at(world, r);
			int final_color = convert_color_to_int(color);
			my_mlx_pixel_put(vars, x, y, final_color);
            x++;
        }
        y++;
    }
    printf("Finished\n");
}


int	handle_close(t_vars *vars)
{
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	vars->img.img_ptr = NULL;
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	vars->mlx = NULL;
    free_scene_data(vars->scene);
	exit(EXIT_SUCCESS);
}

int key_hook(int keycode, t_vars *vars)
{
    if (keycode == XK_Escape)
        handle_close(vars);
    return (0);
}

int	main(int ac, char **av)
{
    t_vars          vars;
	t_scene_data	scene_data;

    vars.mlx = mlx_init();
	if (init_data(&scene_data, ac, av, vars.mlx) == NULL)
    {
		error("Problem with Parsing");
        handle_close(&vars);
        exit(EXIT_FAILURE);
    }
    vars.scene = &scene_data;
	printf("shape count : %d\n", scene_data.shape_count);
    scene_data.mlx = vars.mlx;

    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length,
                                     &vars.img.endian);
    mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, handle_close, &vars);
    mlx_key_hook(vars.win, key_hook, &vars);
    render_scene(&vars, &scene_data);

    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);
    handle_close(&vars);
    return (0);
}
