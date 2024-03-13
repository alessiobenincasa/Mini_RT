/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:17:19 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/13 16:33:32 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_cylinder	init_cylinder(void)
{
	t_cylinder cylinder;

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
	t_vars		vars;
	t_cylinder cylinder;

	cylinder = init_cylinder();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	render_cylinder_basic(&vars, cylinder);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
