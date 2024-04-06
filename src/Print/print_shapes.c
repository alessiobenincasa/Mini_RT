/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:55:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:02:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_sphere(const t_sphere *s)
{
	printf("\033[34m");
	printf("---------------\n");
	printf("Sphere:\n");
	printf("Center: (%f, %f, %f)\n", s->center.x, s->center.y, s->center.z);
	printf("Diameter: %f\n", s->radius);
	printf("Color: (%f, %f, %f)\n", s->material.color.red,
		s->material.color.green, s->material.color.blue);
	printf("Scaling: (%f, %f, %f)\n", s->scale.x, s->scale.y, s->scale.z);
	printf("Motif: %s\n", s->motif);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_plane(const t_plane *p)
{
	printf("\033[32m");
	printf("---------------\n");
	printf("Plane:\n");
	printf("Point: (%f, %f, %f)\n", p->point.x, p->point.y, p->point.z);
	printf("Normal: (%f, %f, %f)\n", p->normal.x, p->normal.y, p->normal.z);
	printf("Color: (%f, %f, %f)\n", p->material.color.red,
		p->material.color.green, p->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_cylinder(const t_cylinder *cyl)
{
	printf("\033[36m");
	printf("---------------\n");
	printf("Cylinder Properties:\n");
	printf("Center: (%.2f, %.2f, %.2f)\n", cyl->center.x, cyl->center.y,
		cyl->center.z);
	printf("Direction: (%.2f, %.2f, %.2f)\n", cyl->direction.x,
		cyl->direction.y, cyl->direction.z);
	printf("Diameter: %.2f\n", cyl->diameter);
	printf("Height: %.2f\n", cyl->maximum);
	printf("Color: (%f, %f, %f)\n", cyl->material.color.red,
		cyl->material.color.green, cyl->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}

void	print_cone(const t_cone *cone)
{
	printf("\033[36m");
	printf("---------------\n");
	printf("Cone Properties:\n");
	printf("Center: (%.2f, %.2f, %.2f)\n", cone->center.x, cone->center.y,
		cone->center.z);
	printf("Direction: (%.2f, %.2f, %.2f)\n", cone->direction.x,
		cone->direction.y, cone->direction.z);
	printf("Maximum: %.2f\n", cone->maximum);
	printf("Color: (%f, %f, %f)\n", cone->material.color.red,
		cone->material.color.green, cone->material.color.blue);
	printf("---------------\n");
	printf("\033[0m");
}

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
