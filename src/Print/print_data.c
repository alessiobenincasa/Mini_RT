/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:59 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 18:36:30 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_identifier_type(t_identifier_type type)
{
	printf("--> Identifier is : ");
	if (type == AMBIENT_LIGHT)
		printf("AMBIENT_LIGHT\n");
	else if (type == CAMERA)
		printf("CAMERA\n");
	else if (type == LIGHT)
		printf("LIGHT\n");
	else if (type == SPHERE)
		printf("SPHERE\n");
	else if (type == PLANE)
		printf("PLANE\n");
	else if (type == CYLINDER)
		printf("CYLINDER\n");
	else
		printf("Unknown type\n");
}

void	print_camera(const t_camera *camera)
{
	printf("\033[35m");
	printf("---------------\n");
	printf("Camera:\n");
	printf("Position: x = %f, y = %f, z = %f\n", camera->position.x,
		camera->position.y, camera->position.z);
	printf("Orientation: x = %f, y = %f, z = %f\n", camera->orientation.x,
		camera->orientation.y, camera->orientation.z);
	printf("FOV: %f\n", camera->fov);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_sphere(const t_sphere *sphere)
{
	printf("\033[34m");
	printf("---------------\n");
	printf("Sphere:\n");
	printf("Center: (%f, %f, %f)\n", sphere->center.x, sphere->center.y,
		sphere->center.z);
	printf("Diameter: %f\n", sphere->diameter);
	printf("Color: (%d, %d, %d)\n", sphere->color[0], sphere->color[1],
		sphere->color[2]);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_ambient(const t_ambient *ambient)
{
	printf("\033[31m");
	printf("---------------\n");
	printf("Ambient:\n");
	printf("Ratio: %f\n", ambient->ratio);
	printf("Color: (%d, %d, %d)\n", ambient->color[0], ambient->color[1],
		ambient->color[2]);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_light(const t_light *light)
{
	printf("\033[33m");
	printf("---------------\n");
	printf("Light:\n");
	printf("Position: (%f, %f, %f)\n", light->position.x, light->position.y,
		light->position.z);
	printf("Intensity: %f\n", light->intensity);
	printf("Color: (%d, %d, %d)\n", light->color[0], light->color[1],
		light->color[2]);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_plane(const t_plane *plane)
{
	printf("\033[37m");
	printf("---------------\n");
	printf("Plane:\n");
	printf("Point: (%f, %f, %f)\n", plane->point.x, plane->point.y,
		plane->point.z);
	printf("Normal: (%f, %f, %f)\n", plane->normal.x, plane->normal.y,
		plane->normal.z);
	printf("Color: (%d, %d, %d)\n", plane->color[0], plane->color[1],
		plane->color[2]);
	printf("---------------\n");
	printf("\033[0m");
}
