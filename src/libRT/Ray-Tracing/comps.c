/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:20:40 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 10:26:03 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_comps	comps_init(void)
{
	t_comps	c;

	c.t = 0.0;
	c.type = NONE;
	c.point = point(0,0,0);
	c.eyev = vector(0,0,0);
	c.normalv = vector(0,0,0);
	c.over_point = point(0,0,0);
	c.inside = 0;
	return (c);
}

static t_tuple	get_normalv(t_id_type type, t_object_union *obj, t_tuple point)
{
	t_tuple	normalv;

	normalv = vector(0, 0, 0);
	if (type == SPHERE)
		normalv = normal_at(*obj->sphere, point);
	else if (type == PLANE)
		normalv = obj->plane->normal;
	else if (type == CYLINDER)
		normalv = normal_at_cylinder(*obj->cylinder, point);
	else if (type == CONE)
		normalv = normal_at_cone(*obj->cone, point);
	return (normalv);
}

t_comps	prepare_computations(t_intersection i, t_ray r)
{
	t_comps	comps;

	comps.t = i.t;
	comps.point = position(r, comps.t);
	comps.eyev = negate_tuple(r.direction);
	comps.type = i.type;
	comps.object = i.object;
	comps.normalv = get_normalv(comps.type, &comps.object, comps.point);

	if (dot(comps.normalv, comps.eyev) < -EPSILON)
	{
		comps.inside = 1;
		comps.normalv = negate_tuple(comps.normalv);
	}
	comps.over_point = add_tuples(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	return (comps);
}
