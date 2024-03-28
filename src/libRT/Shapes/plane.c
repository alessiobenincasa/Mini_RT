/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:37:26 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/28 09:03:38 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// void	set_transform_shape(t_shape *s, t_matrix t)
// {
// 	if (s != NULL)
// 		s->transform = t;
// }

// t_intersections	intersect_shape(t_shape *shape, t_ray r)
// {
// 	t_matrix	inverse_transform;
// 	t_ray		transformed_ray;

// 	inverse_transform = inverse(shape->transform);
// 	transformed_ray = transform(r, inverse_transform);
// 	return (shape->local_intersect(shape, transformed_ray));
// }

// t_intersections	local_intersect(t_shape *shape, t_ray r)
// {
// 	t_intersections	xs;

// 	if (shape->saved_ray)
// 		free(shape->saved_ray);
// 	shape->saved_ray = (t_ray *)malloc(sizeof(t_ray));
// 	*(shape->saved_ray) = r;
// 	xs.count = 0;
// 	xs.intersections = NULL;
// 	return (xs);
// }

// t_tuple	local_normal_at_test(t_shape *shape, t_tuple local_point)
// {
// 	(void)shape;
// 	return (local_point);
// }
// t_tuple	local_normal_at_plane(t_plane plane, t_tuple local_point)
// {
// 	(void)local_point;
// 	return (plane.normal);
// }

// t_shape	*test_shape(void)
// {
// 	t_shape	*s;

// 	s = malloc(sizeof(t_shape));
// 	if (!s)
// 		return (NULL);
// 	s->material = material();
// 	s->saved_ray = NULL;
// 	s->transform = identity_matrix();
// 	s->local_intersect = local_intersect;
// 	s->local_normal_at = local_normal_at_test;
// 	return (s);
// }

// t_tuple	normal_at_shape(t_shape *s, t_tuple p)
// {
// 	t_matrix	inverse_transform;
// 	t_tuple		local_point;
// 	t_tuple		local_normal;
// 	t_matrix	transposed;
// 	t_tuple		world_normal;

// 	inverse_transform = inverse(s->transform);
// 	local_point = multiply_matrix_tuple(inverse_transform, p);
// 	local_normal = local_normal_at_test(s, local_point);
// 	transposed = transpose_matrix(inverse_transform);
// 	world_normal = multiply_matrix_tuple(transposed, local_normal);
// 	world_normal.w = 0;
// 	return (normalize(world_normal));
// }

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
	if (fabs(r.direction.y) < EPSILON)
		return (xs);
	xs.count = 1;
	xs.intersections = malloc(xs.count * sizeof(t_intersection));
	xs.intersections[0].type = PLANE;
	xs.intersections[0].plane = p;
	xs.intersections[0].t = -r.origin.y / r.direction.y;
    return (xs);
}
