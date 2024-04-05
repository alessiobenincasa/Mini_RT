/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:32:48 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 14:58:10 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_coef
{
	double				a;
	double				b;
	double				c;
	double				disc;
	double				t1;
	double				t2;
}						t_coef;

static t_coef	calculate_quadratic_coefficients(t_cylinder *cyl, t_ray tr_ray)
{
	double	radius;
	t_coef	coef;

	radius = cyl->diameter / 2;
	coef.a = pow(tr_ray.direction.x, 2) + pow(tr_ray.direction.z, 2);
	coef.b = 2 * tr_ray.origin.x * tr_ray.direction.x + 2 * tr_ray.origin.z
		* tr_ray.direction.z;
	coef.c = pow(tr_ray.origin.x, 2) + pow(tr_ray.origin.z, 2) - pow(radius, 2);
	return (coef);
}

static t_coef	solve_cylinder_quadratic(t_cylinder *cyl, t_ray tr_ray)
{
	t_coef	coef;
	t_coef	result;
	double	disc;
	double	sqrt_disc;
	double	temp;

	coef = calculate_quadratic_coefficients(cyl, tr_ray);
	disc = coef.b * coef.b - 4 * coef.a * coef.c;
	result.disc = disc;
	if (disc >= 0)
	{
		sqrt_disc = sqrt(disc);
		result.t1 = (-coef.b - sqrt_disc) / (2 * coef.a);
		result.t2 = (-coef.b + sqrt_disc) / (2 * coef.a);
		if (result.t1 > result.t2)
		{
			temp = result.t1;
			result.t1 = result.t2;
			result.t2 = temp;
		}
	}
	return (result);
}

static t_intersections	intersect_cylinder_sides(t_cylinder *cyl, t_ray tr_ray)
{
	t_intersections	xs;
	t_coef			coef;
	double			y0;
	double			y1;

	xs.count = 0;
	xs.intersections = NULL;
	coef = solve_cylinder_quadratic(cyl, tr_ray);
	if (coef.disc >= 0)
	{
		y0 = tr_ray.origin.y + coef.t1 * tr_ray.direction.y;
		if (y0 > cyl->minimum && y0 < cyl->maximum)
			add_intersection_cylinder(&xs, coef.t1, cyl);
		y1 = tr_ray.origin.y + coef.t2 * tr_ray.direction.y;
		if (coef.t1 != coef.t2 && y1 > cyl->minimum && y1 < cyl->maximum)
			add_intersection_cylinder(&xs, coef.t2, cyl);
	}
	return (xs);
}

t_intersections	intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_intersections	xs;
	double			radius;
	t_ray			tr_ray;
	double			t_lower;
	double			t_upper;

	xs = intersect_cylinder_sides(cyl, transform(ray, inverse(cyl->transform)));
	if (cyl->closed && fabs(ray.direction.y) > EPSILON)
	{
		radius = cyl->diameter / 2;
		tr_ray = transform(ray, inverse(cyl->transform));
		t_lower = (cyl->minimum - tr_ray.origin.y) / tr_ray.direction.y;
		if (check_cap(tr_ray, t_lower, radius))
			add_intersection_cylinder(&xs, t_lower, cyl);
		t_upper = (cyl->maximum - tr_ray.origin.y) / tr_ray.direction.y;
		if (check_cap(tr_ray, t_upper, radius))
			add_intersection_cylinder(&xs, t_upper, cyl);
	}
	return (xs);
}

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
	t_tuple		object_point;
	t_tuple		object_normal;
	t_tuple		world_normal;
	t_matrix	inverse_transform;
	t_matrix	transposed_inverse;

	object_point = multiply_matrix_tuple(inverse(cylinder.transform), p);
	object_normal = local_normal_at_cylinder(cylinder, object_point);
	inverse_transform = inverse(cylinder.transform);
	transposed_inverse = transpose_matrix(inverse_transform);
	world_normal = multiply_matrix_tuple(transposed_inverse, object_normal);
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
