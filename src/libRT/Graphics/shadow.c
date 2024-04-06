/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:11:49 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 10:40:21 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_shadow
{
	t_tuple	v;
	t_tuple	new_point;
	t_tuple	direction;
	double	distance;
}			t_shadow;

t_shadow	shadow_init(t_tuple point, t_tuple light_pos)
{
	t_shadow	data;

	data.v = subtract_tuples(light_pos, point);
	data.distance = magnitude(data.v);
	data.direction = normalize(data.v);
	data.new_point = add_tuples(point, multiply_tuple_scalar(data.direction,
				EPSILON));
	return (data);
}

int	is_shadowed(t_world world, t_tuple point, t_tuple light_pos)
{
	t_shadow		data;
	t_ray			r;
	t_intersections	inters;
	t_intersection	*h;

	h = NULL;
	data = shadow_init(point, light_pos);
	r = ray(data.new_point, data.direction);
	inters = intersect_world(&world, r);
	h = hit(&inters);
	if (h != NULL && h->t < data.distance)
	{
		free(inters.intersections);
		return (1);
	}
	free(inters.intersections);
	return (0);
}
