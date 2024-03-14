/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 16:58:20 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_cylinder	init_cylinder(void)
{
	t_cylinder	cylinder;

	cylinder.center.x = 50.0;
	cylinder.center.y = 0.0;
	cylinder.center.z = 20.6;
	cylinder.direction.x = 0.0;
	cylinder.direction.y = 0.0;
	cylinder.direction.z = 1.0;
	cylinder.diameter = 14.2;
	cylinder.height = 21.42;
	cylinder.color[0] = 10;
	cylinder.color[1] = 0;
	cylinder.color[2] = 255;
	return (cylinder);
}

int	main(void)
{
	t_vars	vars;
	t_plane	plane;

	plane.point = (t_vector){0.0, 0.0, 0.0};
	plane.normal = (t_vector){0.0, 1.0, 0.0};
	plane.color[0] = 255;
	plane.color[1] = 0;
	plane.color[2] = 255;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT - Plane");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	render_plane(&vars, plane);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
