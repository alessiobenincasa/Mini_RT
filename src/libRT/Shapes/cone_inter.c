/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:09:47 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 20:38:20 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_coef
{
	double		a;
	double		b;
	double		c;
}				t_coef;

typedef struct s_cone_context
{
	t_cone		*cone;
	t_ray		transformed_ray;
	double		min;
	double		max;
}				t_cone_context;

void	calculate_and_sort_roots(t_coef coeffs, double *t0, double *t1)
{
	double	disc;
	double	temp;

	disc = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	if (disc < 0)
	{
		*t0 = -1;
		*t1 = -1;
		return ;
	}
	*t0 = (-coeffs.b - sqrt(disc)) / (2 * coeffs.a);
	*t1 = (-coeffs.b + sqrt(disc)) / (2 * coeffs.a);
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
}

void	validate_and_add_intersection(double t, double min, double max,
		t_ray ray, t_cone *cone, t_intersections *xs)
{
	double	y;

	y = ray.origin.y + t * ray.direction.y;
	if (y > min && y < max)
		add_intersection_cone(xs, t, cone);
}

void	intersect_cone_sides(t_cone *cone, t_ray transformed_ray,
		t_intersections *xs)
{
	t_coef	coeffs;
	double	t0;
	double	t1;

	calculate_coefficients(transformed_ray, &coeffs.a, &coeffs.b, &coeffs.c);
	calculate_and_sort_roots(coeffs, &t0, &t1);
	if (t0 != -1 && t1 != -1)
	{
		validate_and_add_intersection(t0, cone->minimum, cone->maximum,
			transformed_ray, cone, xs);
		validate_and_add_intersection(t1, cone->minimum, cone->maximum,
			transformed_ray, cone, xs);
	}
}

void	intersect_cone_caps(t_cone *cone, t_ray transformed_ray,
		t_intersections *xs)
{
	double	t_lower;
	double	t_upper;

	t_lower = (cone->minimum - transformed_ray.origin.y)
		/ transformed_ray.direction.y;
	if (check_cap_cone(transformed_ray, t_lower, cone, 1))
		add_intersection_cone(xs, t_lower, cone);
	t_upper = (cone->maximum - transformed_ray.origin.y)
		/ transformed_ray.direction.y;
	if (check_cap_cone(transformed_ray, t_upper, cone, 0))
		add_intersection_cone(xs, t_upper, cone);
}

t_intersections	intersect_cone(t_cone *cone, t_ray r)
{
	t_intersections	xs;
	t_ray			transformed_ray;

	xs.count = 0;
	xs.intersections = NULL;
	transformed_ray = transform(r, inverse(cone->transform));
	intersect_cone_sides(cone, transformed_ray, &xs);
	intersect_cone_caps(cone, transformed_ray, &xs);
	return (xs);
}
