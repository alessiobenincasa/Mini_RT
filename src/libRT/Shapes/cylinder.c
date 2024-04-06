/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:32:48 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 12:32:28 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	check_cap(t_ray ray, double t, double radius)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((x * x + z * z) <= (radius * radius));
}

t_cylinder	cylinder(void)
{
	t_cylinder	cyl;

	cyl.transform = identity_matrix();
	cyl.minimum = 0;
	cyl.maximum = 3;
	cyl.closed = 1;
	cyl.material = material();
	cyl.material.specular = 0;
	cyl.material.diffuse = 0.6;
	cyl.material.shininess = 50;
	return (cyl);
}

t_tuple	local_normal_at_cylinder(t_cylinder cyl, t_tuple point)
{
	double	radius;
	double	dist;

	radius = cyl.diameter / 2;
	dist = pow(point.x, 2) + pow(point.z, 2);
	if (dist < pow(radius, 2) && point.y >= cyl.maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < pow(radius, 2) && point.y <= cyl.minimum + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
}

t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple p)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = mult_mat_tup(inverse(cylinder.transform), p);
	object_normal = local_normal_at_cylinder(cylinder, object_point);
	world_normal = mult_mat_tup(transpose_matrix(inverse(cylinder.transform)),
			object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

void	add_intersection_cylinder(t_intersections *xs, double t,
		t_cylinder *cyl)
{
	xs->count++;
	xs->intersections = realloc(xs->intersections, xs->count
			* sizeof(t_intersection));
	xs->intersections[xs->count - 1].t = t;
	xs->intersections[xs->count - 1].object.cylinder = cyl;
	xs->intersections[xs->count - 1].type = CYLINDER;
}
