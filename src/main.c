/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c			                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/29 14:08:17 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	transfer_scene_data_to_world(t_scene_data *scene, t_world *world)
{
	world->objects = scene->shapes;
	world->object_count = scene->shape_count;
	world->extra_lights = scene->extra_lights;
	if (scene->light)
		world->light = *(scene->light);
}

typedef struct s_render
{
	int		final_color;
	int		x;
	int		y;
}			t_render;

t_render	set_render_values(void)
{
	t_render	render;

	render.final_color = 0;
	render.x = -1;
	render.y = -1;
	return (render);
}

void	render_scene(t_vars *vars, t_scene_data *scene)
{
	t_render	render;
	t_world		world;
	t_camera	cam;
	t_ray		r;
	t_color		pix_color;

	render = set_render_values();
	world = world_init();
	pix_color = color(0, 0, 0);
	transfer_scene_data_to_world(scene, &world);
	print_data(world, scene);
	cam = prepare_camera(scene->camera);
	while (++(render.y) < HEIGHT)
	{
		render.x = -1;
		while (++(render.x) < WIDTH)
		{
			r = ray_for_pixel(cam, render.x, render.y);
			pix_color = color_at(world, r);
			render.final_color = convert_color_to_int(pix_color);
			my_mlx_pixel_put(vars, render.x, render.y, render.final_color);
		}
	}
	printf("Compilation Finished.\nEnjoy The View\n");
}

int	main(int ac, char **av)
{
	t_vars			vars;
	t_scene_data	scene_data;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	vars.scene = NULL;
	if (init_data(&scene_data, ac, av, vars.mlx) == NULL)
		handle_close(&vars);
	vars.scene = &scene_data;
	scene_data.mlx = vars.mlx;
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, handle_close, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	print_header();
	render_scene(&vars, &scene_data);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	handle_close(&vars);
	return (0);
}
