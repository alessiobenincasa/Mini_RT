/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:27:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/04 17:16:52 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_cone	cone(void)
{
	t_cone	cone;

	cone.transform = identity_matrix();
	cone.minimum = 0;
	cone.maximum = 3;
	cone.closed = 1;
	cone.inverted = 1;
	cone.material = material();
	cone.material.specular = 0;
	cone.material.diffuse = 0.6;
	cone.material.shininess = 50;
	return (cone);
}

t_tuple	local_normal_at_cone(t_cone cone, t_tuple point)
{
	double	radius;
	double	dist;
	double	slant_height;
	double	height;
	double	slope;
	double	y;

	radius = cone.maximum / 2;
	dist = pow(point.x, 2) + pow(point.z, 2);
	if (dist < pow(cone.maximum, 2) && point.y >= cone.maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < pow(cone.maximum, 2) && point.y <= cone.minimum + EPSILON)
		return (vector(0, -1, 0));
	else
	{
		slant_height = sqrt(pow(point.x, 2) + pow(point.z, 2));
		height = fabs(cone.maximum - cone.minimum);
		slope = radius / height;
		y = slope * slant_height;
		if (cone.inverted)
			y = -y;
		return (vector(point.x, y, point.z));
	}
}

t_tuple normal_at_cone(t_cone cone, t_tuple p)
{
    t_tuple object_point = multiply_matrix_tuple(inverse(cone.transform), p);
    t_tuple object = local_normal_at_cone(cone, object_point);
    t_matrix inverse_transform = inverse(cone.transform);
    t_matrix transposed = transpose_matrix(inverse_transform);
    t_tuple world_normal = multiply_matrix_tuple(transposed, object);
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
	if ((x * x + z * z) <= (cap * cap))
		return (1);
	else
		return (0);
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

static t_intersections	intersect_cone_sides(t_cone *cone,
		t_ray transformed_ray)
{
	t_intersections	xs;
	double			sqrt_disc;
	double			a;
	double			b;
	double			c;
	double			disc;
	double			t0;
	double			t1;
	double			temp;
	double			y0;
	double			y1;

	xs.count = 0;
	xs.intersections = NULL;
	a = pow(transformed_ray.direction.x, 2) - pow(transformed_ray.direction.y,
			2) + pow(transformed_ray.direction.z, 2);
	b = 2 * transformed_ray.origin.x * transformed_ray.direction.x - 2
		* transformed_ray.origin.y * transformed_ray.direction.y + 2
		* transformed_ray.origin.z * transformed_ray.direction.z;
	c = pow(transformed_ray.origin.x, 2) - pow(transformed_ray.origin.y, 2)
		+ pow(transformed_ray.origin.z, 2);
	disc = b * b - 4 * a * c;
	if (fabs(a) >= EPSILON && disc >= 0)
	{
		sqrt_disc = sqrt(disc);
		t0 = (-b - sqrt_disc) / (2 * a);
		t1 = (-b + sqrt_disc) / (2 * a);
		if (t0 > t1)
		{
			temp = t0;
			t0 = t1;
			t1 = temp;
		}
		y0 = transformed_ray.origin.y + t0 * transformed_ray.direction.y;
		y1 = transformed_ray.origin.y + t1 * transformed_ray.direction.y;
		if (y0 > cone->minimum && y0 < cone->maximum)
			add_intersection_cone(&xs, t0, cone);
		if (y1 > cone->minimum && y1 < cone->maximum)
			add_intersection_cone(&xs, t1, cone);
	}
	return (xs);
}

t_intersections	intersect_cone(t_cone *cone, t_ray r)
{
	t_intersections	xs;
	t_ray			transformed_ray;
	double			t_lower;
	double			t_upper;

	transformed_ray = transform(r, inverse(cone->transform));
	xs = intersect_cone_sides(cone, transformed_ray);
	if (cone->closed && fabs(transformed_ray.direction.y) > EPSILON)
	{
		t_lower = (cone->minimum - transformed_ray.origin.y)
			/ transformed_ray.direction.y;
		if (check_cap_cone(transformed_ray, t_lower, cone, 1))
			add_intersection_cone(&xs, t_lower, cone);
		t_upper = (cone->maximum - transformed_ray.origin.y)
			/ transformed_ray.direction.y;
		if (check_cap_cone(transformed_ray, t_upper, cone, 0))
			add_intersection_cone(&xs, t_upper, cone);
	}
	return (xs);
}
