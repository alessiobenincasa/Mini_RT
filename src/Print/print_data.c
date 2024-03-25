/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:59 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 14:59:42 by svolodin         ###   ########.fr       */
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
	printf("Diameter: %f\n", sphere->radius);
	printf("Color: (%f, %f, %f)\n", sphere->material.color.red, sphere->material.color.green,
		sphere->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_ambient(const t_ambient *ambient)
{
	printf("\033[31m");
	printf("---------------\n");
	printf("Ambient:\n");
	printf("Ratio: %f\n", ambient->ratio);
	printf("Color: (%f, %f, %f)\n", ambient->color.red, ambient->color.green,
		ambient->color.blue);
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
	printf("Intensity: %f\n", light->energy);
	printf("Color: (%f, %f, %f)\n", light->intensity.red, light->intensity.green,
		light->intensity.blue);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_plane(const t_plane *plane)
{
	printf("\033[32m");
	printf("---------------\n");
	printf("Plane:\n");
	printf("Point: (%f, %f, %f)\n", plane->point.x, plane->point.y,
		plane->point.z);
	printf("Normal: (%f, %f, %f)\n", plane->normal.x, plane->normal.y,
		plane->normal.z);
	printf("Color: (%f, %f, %f)\n", plane->material.color.red, plane->material.color.green,
		plane->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}
void	print_cylinder(const t_cylinder *cylinder)
{
	printf("\033[36m");
	printf("---------------\n");
	printf("Cylinder Properties:\n");
	printf("Center: (%.2f, %.2f, %.2f)\n", cylinder->center.x, cylinder->center.y,
		cylinder->center.z);
	printf("Direction: (%.2f, %.2f, %.2f)\n", cylinder->direction.x,
		cylinder->direction.y, cylinder->direction.z);
	printf("Diameter: %.2f\n", cylinder->diameter);
	printf("Height: %.2f\n", cylinder->height);
	printf("Color: (%f, %f, %f)\n", cylinder->material.color.red, cylinder->material.color.green,
		cylinder->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}
