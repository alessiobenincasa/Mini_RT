/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:37:26 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/29 08:38:14 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_plane			plane(void);
t_intersections	intersect_plane(t_plane *p, t_ray r);


t_plane	plane(void)
{
	t_plane	p;

	p.point = point(0, 0, 0);
	p.normal = vector(0, 1, 0);
	p.material = material();
	p.transform = identity_matrix();
	return (p);
}

t_intersections	intersect_plane(t_plane *p, t_ray r)
{
	t_intersections	xs;

	xs.count = 0;
	xs.intersections = NULL;
	
	double	denominator = dot(r.direction, p->normal);
	if (fabs(denominator) < EPSILON)
		return (xs);

	t_tuple plane_to_ray = subtract_tuples(r.origin, p->point);
	double t = -dot(plane_to_ray, p->normal) / denominator;
	if (t < EPSILON)
		return (xs);

	xs.count = 1;
	xs.intersections = malloc(xs.count * sizeof(t_intersection));
	if (xs.intersections == NULL)
		exit(EXIT_FAILURE);
	xs.intersections[0].t = t;
	xs.intersections[0].plane = p;
	xs.intersections[0].type = PLANE;
    return (xs);
}
