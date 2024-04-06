/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:27:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 12:32:27 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tuple	calculate_cone_body_normal(t_cone cone, t_tuple point)
{
	double	radius;
	double	slant_height;
	double	height;
	double	slope;
	double	y;

	radius = cone.maximum / 2;
	slant_height = sqrt(pow(point.x, 2) + pow(point.z, 2));
	height = fabs(cone.maximum - cone.minimum);
	slope = radius / height;
	y = slope * slant_height;
	if (cone.inverted)
		y = -y;
	return (vector(point.x, y, point.z));
}

t_tuple	local_normal_at_cone(t_cone cone, t_tuple point)
{
	double	dist;

	dist = pow(point.x, 2) + pow(point.z, 2);
	if (dist < pow(cone.maximum, 2) && point.y >= cone.maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < pow(cone.maximum, 2) && point.y <= cone.minimum + EPSILON)
		return (vector(0, -1, 0));
	else
		return (calculate_cone_body_normal(cone, point));
}

t_tuple	normal_at_cone(t_cone cone, t_tuple p)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = mult_mat_tup(inverse(cone.transform), p);
	object_normal = local_normal_at_cone(cone, object_point);
	world_normal = mult_mat_tup(transpose_matrix(inverse(cone.transform)),
			object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

int	check_cap_cone(t_ray ray, double t, t_cone *cone, int is_lower)
{
	double	x;
	double	z;
	double	cap;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if (is_lower)
		cap = cone->minimum;
	else
		cap = cone->maximum;
	return ((x * x + z * z) <= (cap * cap));
}

void	add_intersection_cone(t_intersections *xs, double t, t_cone *cone)
{
	xs->count++;
	xs->intersections = realloc(xs->intersections, xs->count
			* sizeof(t_intersection));
	xs->intersections[xs->count - 1].t = t;
	xs->intersections[xs->count - 1].object.cone = cone;
	xs->intersections[xs->count - 1].type = CONE;
}
