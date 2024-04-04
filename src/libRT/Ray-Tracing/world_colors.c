/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/04 10:20:39 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_intersections	intersect_world(t_world *world, t_ray r);
t_comps			prepare_computations(t_intersection i, t_ray r);
t_color			shade_hit(t_world world, t_comps comps);
t_color			color_at(t_world w, t_ray r);
t_matrix		view_transform(t_tuple from, t_tuple to, t_tuple up);

static t_intersections	intersect_object(void *object, t_ray r, t_id_type type)
{
    t_intersections xs;

	xs.capacity = 0;
	xs.count = 0;
	xs.intersections = NULL;
	if (type == SPHERE)
		xs = intersect_sphere((t_sphere *)object, r);
	else if (type == PLANE)
		xs = intersect_plane((t_plane *)object, r);
	else if (type == CYLINDER)
		xs = intersect_cylinder((t_cylinder *)object, r);
	else if (type == CONE)
		xs = intersect_cone((t_cone *)object, r);

    return (xs);
}

t_intersections intersect_world(t_world *world, t_ray r)
{
    t_intersections xs;
	t_intersections temp_xs;
    t_list *current;
	int i;
	int j;
	
	xs.count = 0;
	xs.intersections = NULL;
	current = world->objects;
	i = -1;
	while (++i < world->object_count)
    {
        temp_xs = intersect_object(current->content, r, current->type);
		j = -1;
		while (++j < temp_xs.count)
            add_intersection(&xs, temp_xs.intersections[j]);
        current = current->next;
    }

    sort_intersections(&xs);
    return xs;
}

t_tuple	get_normalv(t_id_type type, t_object_union *obj, t_tuple point)
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

t_material	extract_material_comps(t_comps comps)
{
	t_material	m;

	if (comps.type == SPHERE)
		m = comps.object.sphere->material;
	else if (comps.type == PLANE)
		m = comps.object.plane->material;
	else if (comps.type == CYLINDER)
		m = comps.object.cylinder->material;
	else if (comps.type == CONE)
		m = comps.object.cone->material;
	else
		m = material();
	return (m);
}


t_color shade_hit(t_world world, t_comps comps)
{
	t_color		total_light;
	t_material	material;
	int			in_shadow;
	t_list		*current_light;

	material = extract_material_comps(comps);
	in_shadow = is_shadowed(world, comps.over_point, world.light.position);
	total_light = lighting(material, world.light, comps, in_shadow);
	current_light = world.extra_lights;
	while (current_light != NULL)
	{
		t_light *light = (t_light *)(current_light->content);
		in_shadow = is_shadowed(world, comps.over_point, light->position);
		total_light = add_colors(total_light, lighting(material, *light, comps, in_shadow));
		current_light = current_light->next;
	}
	return (total_light);
}

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


t_color	color_at(t_world w, t_ray r)
{
	t_intersections	xs;
	t_intersection	*i;
	t_comps			comps;
	t_color			result;

	comps = comps_init();
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
