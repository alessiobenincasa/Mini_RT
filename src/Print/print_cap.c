/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:57:55 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 08:58:26 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_camera(const t_camera *c)
{
	printf("\033[35m");
	printf("---------------\n");
	printf("Camera:\n");
	printf("Position: x = %f, y = %f, z = %f\n", c->position.x, c->position.y,
		c->position.z);
	printf("Orientation: x = %f, y = %f, z = %f\n", c->orientation.x,
		c->orientation.y, c->orientation.z);
	printf("FOV: %f\n", c->fov);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_camera_direction(t_tuple from, t_tuple to, t_tuple up)
{
	printf("\033[35m");
	printf("---------------\n");
	printf("Camera Looking:\n");
	printf("FROM: x = %f, y = %f, z = %f\n", from.x, from.y, from.z);
	printf("TO: x = %f, y = %f, z = %f\n", to.x, to.y, to.z);
	printf("UP: x = %f, y = %f, z = %f\n", up.x, up.y, up.z);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_light(const t_light *l)
{
	printf("\033[33m");
	printf("---------------\n");
	printf("Light:\n");
	printf("Position: (%f, %f, %f)\n", l->position.x, l->position.y,
		l->position.z);
	printf("Intensity: %f\n", l->energy);
	printf("Color: (%f, %f, %f)\n", l->intensity.red, l->intensity.green,
		l->intensity.blue);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_ambient(const t_ambient *a)
{
	printf("\033[31m");
	printf("---------------\n");
	printf("Ambient:\n");
	printf("Ratio: %f\n", a->ratio);
	printf("Color: (%f, %f, %f)\n", a->color.red, a->color.green,
		a->color.blue);
	printf("---------------\n");
	printf("\033[0m");
}
