/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:12:24 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_coef
{
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t1;
	double		t2;
}				t_coef;

static t_coef	get_quad_coefs(t_sphere *s, t_ray r)
{
	t_coef	coef;
	t_tuple	sphere_to_ray;

	sphere_to_ray = subtract_tuples(r.origin, s->center);
	coef.a = dot(r.direction, r.direction);
	coef.b = 2.0 * dot(r.direction, sphere_to_ray);
	coef.c = dot(sphere_to_ray, sphere_to_ray) - pow(s->radius, 2);
	coef.disc = pow(coef.b, 2) - 4 * coef.a * coef.c;
	return (coef);
}

static t_coef	solve_quad(t_coef coef)
{
	double	root;
	double	temp;

	root = sqrt(coef.disc);
	coef.t1 = (-coef.b - root) / (2 * coef.a);
	coef.t2 = (-coef.b + root) / (2 * coef.a);
	if (coef.t1 > coef.t2)
	{
		temp = coef.t1;
		coef.t1 = coef.t2;
		coef.t2 = temp;
	}
	return (coef);
}

static t_intersections	create_intersections(t_intersections xs, t_coef coef,
		t_sphere *s)
{
	int	count;

	if (coef.disc == 0)
		count = 1;
	else
		count = 2;
	xs.count = count;
	xs.intersections = ft_calloc(count, sizeof(t_intersection));
	if (xs.intersections == NULL)
		exit(EXIT_FAILURE);
	xs.intersections[0].t = coef.t1;
	xs.intersections[0].object.sphere = s;
	xs.intersections[0].type = SPHERE;
	if (count > 1)
	{
		xs.intersections[1].t = coef.t2;
		xs.intersections[1].object.sphere = s;
		xs.intersections[1].type = SPHERE;
	}
	return (xs);
}

t_intersections	intersect_sphere(t_sphere *s, t_ray r)
{
	t_intersections	xs;
	t_ray			tr_ray;
	t_coef			coef;

	tr_ray = transform_ray(r, s->transform);
	coef = get_quad_coefs(s, tr_ray);
	xs.count = 0;
	xs.intersections = NULL;
	if (coef.disc < 0)
		return (xs);
	coef = solve_quad(coef);
	xs = create_intersections(xs, coef, s);
	return (xs);
}
