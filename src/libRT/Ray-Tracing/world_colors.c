/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/26 14:13:02 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersections	intersect_world(t_world *world, t_ray r);
t_comps			prepare_computations(t_intersection i, t_ray r);
t_color			shade_hit(t_world world, t_comps comps);
t_color			color_at(t_world w, t_ray r);
t_matrix		view_transform(t_tuple from, t_tuple to, t_tuple up);

t_intersections	intersect_world(t_world *world, t_ray r)
{
	t_intersections	sphere_xs;
	t_intersections xs = {0, 0};

	t_sphere	*s;
	t_list		*current = world->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			s = (t_sphere *)current->content;
			sphere_xs = intersect(s, r);
			for (int j = 0; j < sphere_xs.count; j++)
			{
				add_intersection(&xs, sphere_xs.intersections[j].t, s);
			}
		}
		current = current->next;
	}
	sort_intersections(&xs);
	return (xs);
}

t_comps prepare_computations(t_intersection i, t_ray r)
{
    t_comps comps;
    comps.t = i.t;
    comps.sphere = i.sphere;
    comps.point = position(r, comps.t);
    comps.eyev = negate_tuple(r.direction);
    comps.normalv = normal_at(*comps.sphere, comps.point);
    if (dot(comps.normalv, comps.eyev) < -EPSILON)
    {
        comps.inside = 1;
        comps.normalv = negate_tuple(comps.normalv);
    }
    else
	{
        comps.inside = 0;
	}
	comps.over_point = add_tuples(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
    return (comps);
}

t_color shade_hit(t_world world, t_comps comps)
{
	int in_shadow = is_shadowed(world, comps.over_point);
	t_color light = lighting(comps.sphere->material, world.light, comps.point, comps.eyev, comps.normalv, in_shadow);
	return (light);
}

t_color	color_at(t_world w, t_ray r)
{
	t_intersections xs = intersect_world(&w, r);
	t_intersection	*i = hit(&xs);
	
	if (!i)
		return (color(0, 0, 0));
	t_comps comps = prepare_computations(*i, r);
	t_color result = shade_hit(w, comps);
	return (result);
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward = normalize(subtract_tuples(to, from));
	t_vector	left = cross(forward, normalize(up));
	t_vector	true_up = cross(vector(left.x ,left.y, left.z), forward);

	float orientation[16] = {
        left.x, left.y, left.z, 0,
        true_up.x, true_up.y, true_up.z, 0,
        -(forward.x), -(forward.y), -(forward.z), 0,
        0, 0, 0, 1
    };
	t_matrix result = create_matrix(4, 4, orientation);
    return (multiply_matrices(result, translation(-from.x, -from.y, -from.z)));
}
