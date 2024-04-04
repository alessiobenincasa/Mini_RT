/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:11:49 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/04 10:55:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	is_shadowed(t_world world, t_tuple point, t_tuple light_pos);

int	is_shadowed(t_world world, t_tuple point, t_tuple light_pos)
{
	t_tuple			v;
	double			distance;
	t_tuple			direction;
	t_ray			r;
	t_intersections	inters;
	t_intersection	*h = NULL;

	v = subtract_tuples(light_pos, point);
	distance = magnitude(v);
	direction = normalize(v);
	r = ray(add_tuples(point, multiply_tuple_scalar(direction, EPSILON)),
			direction);
	inters = intersect_world(&world, r);
	h = hit(&inters);
	// printf("Shadow check: distance to light = %f, closest hit = %f, in shadow = %d\n", 
	// 	distance, (h != NULL ? h->t : -1), (h != NULL && h->t < distance) ? 1 : 0);
	if (h != NULL && h->t < distance)
		return (1);
	return (0);
}
