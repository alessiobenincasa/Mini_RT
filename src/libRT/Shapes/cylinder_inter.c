/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:37:33 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 20:20:19 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_coef
{
	double		a;
	double		b;
	double		c;
}				t_coef;

typedef struct s_cylinder_hit
{
	double		min;
	double		max;
	t_ray		tr_ray;
	t_cylinder	*cyl;
}				t_cylinder_hit;

t_coef	calculate_cylinder_coeffs(t_ray tr_ray, double radius)
{
	t_coef	coeffs;

	coeffs.a = pow(tr_ray.direction.x, 2) + pow(tr_ray.direction.z, 2);
	coeffs.b = 2 * tr_ray.origin.x * tr_ray.direction.x + 2 * tr_ray.origin.z
		* tr_ray.direction.z;
	coeffs.c = pow(tr_ray.origin.x, 2) + pow(tr_ray.origin.z, 2) - pow(radius,
			2);
	return (coeffs);
}

void	find_cylinder_roots(t_coef coeffs, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	if (discriminant < 0)
	{
		*t0 = -1;
		*t1 = -1;
		return ;
	}
	*t0 = (-coeffs.b - sqrt(discriminant)) / (2 * coeffs.a);
	*t1 = (-coeffs.b + sqrt(discriminant)) / (2 * coeffs.a);
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
}

void	check_and_add_cylinder_intersection(t_intersections *xs, double t,
		t_cylinder_hit hit_info)
{
	double	y;

	y = hit_info.tr_ray.origin.y + t * hit_info.tr_ray.direction.y;
	if (y > hit_info.min && y < hit_info.max)
		add_intersection_cylinder(xs, t, hit_info.cyl);
}

void	intersect_cylinder_sides(t_cylinder *cyl, t_ray tr_ray,
		t_intersections *xs, double radius)
{
	t_coef			coeffs;
	t_cylinder_hit	hit_info;
	double			t0;
	double			t1;

	coeffs = calculate_cylinder_coeffs(tr_ray, radius);
	find_cylinder_roots(coeffs, &t0, &t1);
	hit_info.min = cyl->minimum;
	hit_info.max = cyl->maximum;
	hit_info.tr_ray = tr_ray;
	hit_info.cyl = cyl;
	if (t0 != -1)
		check_and_add_cylinder_intersection(xs, t0, hit_info);
	if (t1 != -1)
		check_and_add_cylinder_intersection(xs, t1, hit_info);
}

void	intersect_cylinder_caps(t_cylinder *cyl, t_ray tr_ray,
		t_intersections *xs, double radius)
{
	double	t_lower;
	double	t_upper;

	t_lower = (cyl->minimum - tr_ray.origin.y) / tr_ray.direction.y;
	if (check_cap(tr_ray, t_lower, radius))
		add_intersection_cylinder(xs, t_lower, cyl);
	t_upper = (cyl->maximum - tr_ray.origin.y) / tr_ray.direction.y;
	if (check_cap(tr_ray, t_upper, radius))
		add_intersection_cylinder(xs, t_upper, cyl);
}
