/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:45:42 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 08:46:32 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_coef
{
	double				a;
	double				b;
	double				c;
	double				disc;
}						t_coef;

static double	*solve_quadratic(t_coef coeff)
{
	double			sqrt_disc;
	double			temp;
	static double	roots[2];

	if (coeff.disc < 0)
		return (NULL);
	sqrt_disc = sqrt(coeff.disc);
	roots[0] = (-coeff.b - sqrt_disc) / (2 * coeff.a);
	roots[1] = (-coeff.b + sqrt_disc) / (2 * coeff.a);
	if (roots[0] > roots[1])
	{
		temp = roots[0];
		roots[0] = roots[1];
		roots[1] = temp;
	}
	return (roots);
}

static t_coef	calculate_cone_coefficients(t_ray r)
{
	t_coef	coeff;

	coeff.a = pow(r.direction.x, 2) - pow(r.direction.y, 2) + pow(r.direction.z,
			2);
	coeff.b = 2 * r.origin.x * r.direction.x - 2 * r.origin.y * r.direction.y
		+ 2 * r.origin.z * r.direction.z;
	coeff.c = pow(r.origin.x, 2) - pow(r.origin.y, 2) + pow(r.origin.z, 2);
	coeff.disc = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
	return (coeff);
}

static t_intersections	intersect_cone_sides(t_cone *cone, t_ray r)
{
	t_intersections	xs;
	t_coef			coeff;
	double			*roots;

	xs.count = 0;
	xs.intersections = NULL;
	coeff = calculate_cone_coefficients(r);
	roots = solve_quadratic(coeff);
	process_cone_intersections(&xs, roots, cone, r);
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
