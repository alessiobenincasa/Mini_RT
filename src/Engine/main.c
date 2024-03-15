/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:17:19 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 20:29:06 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_shapes(t_vars *vars, t_scene_data *scene_data)
{
	t_list	*current;

	current = scene_data->shapes;
	while (current)
	{
		print_sphere(current->content);
		render(vars, *(t_sphere *)(current->content), scene_data->light);
		current = current->next;
	}
}

int	main(int ac, char **av)
{
	t_vars			vars;
	t_scene_data	scene_data;

	if (init_data(&scene_data, ac, av) == NULL)
		return (1);
	printf("shape count : %d\n", scene_data.shape_count);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	render_shapes(&vars, &scene_data);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
