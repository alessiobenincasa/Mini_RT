/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/30 17:06:02 by svolodin         ###   ########.fr       */
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
	t_intersections	planes_xs;
	t_intersections	cyl_xs;
	t_sphere		*s;
	t_plane			*p;
	t_cylinder		*cyl;
	t_list			*current;

	t_intersections	xs = {0, 0};
	current = world->objects;
	for (int i = 0; i < world->object_count; i++)
	{
		if (current->type == SPHERE)
		{
			s = (t_sphere *)current->content;
			sphere_xs = intersect(s, r);
			for (int j = 0; j < sphere_xs.count; j++)
			{
				add_intersection(&xs, sphere_xs.intersections[j]);
			}
		}
		else if (current->type == PLANE)
		{
			p = (t_plane *)current->content;
			planes_xs = intersect_plane(p, r);
			for (int j = 0; j < planes_xs.count; j++)
			{
				add_intersection(&xs, planes_xs.intersections[j]);
			}
		}
		else if (current->type == CYLINDER)
		{
			cyl = (t_cylinder *)current->content;
			cyl_xs = local_intersect_cylinder(cyl, r);
			for (int j = 0; j < cyl_xs.count; j++)
			{
				add_intersection(&xs, cyl_xs.intersections[j]);
			}
		}
		current = current->next;
	}
	sort_intersections(&xs);
	return (xs);
}

t_comps	prepare_computations(t_intersection i, t_ray r)
{
	t_comps	comps;

	comps.t = i.t;
	comps.point = position(r, comps.t);
	comps.eyev = negate_tuple(r.direction);
	comps.type = i.type;
	if (comps.type == SPHERE)
	{
		comps.object.sphere = i.sphere;
		comps.normalv = normal_at(*comps.object.sphere, comps.point);
	}
	else if (comps.type == PLANE)
	{
		comps.object.plane = i.plane;
		comps.normalv = comps.object.plane->normal;
	}
	else if (comps.type == CYLINDER)
	{
		comps.object.cylinder = i.cyl;
		comps.normalv = normal_at_cylinder(*comps.object.cylinder, comps.point);
	}
	if (dot(comps.normalv, comps.eyev) < -EPSILON)
	{
		comps.inside = 1;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = 0;
	comps.over_point = add_tuples(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	return (comps);
}

t_material	extract_material_comps(t_comps comps)
{
	t_material	m;

	if (comps.type == SPHERE)
		m = comps.object.sphere->material;
	else if (comps.type == PLANE)
		m = comps.object.plane->material;
	else if (comps.type == CYLINDER)
		m = comps.object.cylinder->material;
	else
		m = material();
	return (m);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	t_color		light;
	t_material	material;
	int			in_shadow;

	material = extract_material_comps(comps);
	in_shadow = is_shadowed(world, comps.over_point);
	light = lighting(material, world.light, comps.point, comps.eyev, comps.normalv, in_shadow);
	return (light);
}

t_color	color_at(t_world w, t_ray r)
{
	t_intersections	xs;
	t_intersection	*i;
	t_comps			comps;
	t_color			result;

	xs = intersect_world(&w, r);
	i = hit(&xs);
	if (!i)
		return (color(0, 0, 0));
	comps = prepare_computations(*i, r);
	result = shade_hit(w, comps);
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
