/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:07:18 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/24 14:30:35 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_world	world(void)
{
	t_world	w;

	w.objects = NULL;
	w.object_count = 0;
	return (w);
}

t_world default_world(void)
{
    t_world w;

    t_sphere *s1 = malloc(sizeof(t_sphere));
    *s1 = sphere();
    set_color(&s1->material.color, 0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    t_sphere *s2 = malloc(sizeof(t_sphere));
    *s2 = sphere();
    s2->transform = scaling(0.5, 0.5, 0.5);

    w.object_count = 2;
    w.objects = malloc(sizeof(t_object) * 2);
    w.objects[0].data = s1;
    w.objects[1].data = s2;

    w.light = point_light(point(-10, 10, -10), color(1, 1, 1));
    return (w);
}

void free_world(t_world *w)
{
    for (int i = 0; i < w->object_count; i++)
	{
        free(w->objects[i].data);
    }
    free(w->objects);
}

void	add_intersection(t_intersections *xs, double t, t_sphere *s)
{
	int	new_count;

	new_count = xs->count + 1;
	xs->intersections = realloc(xs->intersections, new_count
			* sizeof(t_intersection));
	if (xs->intersections == NULL)
		exit(EXIT_FAILURE);
	xs->intersections[xs->count].t = t;
	xs->intersections[xs->count].sphere = s;
	xs->count = new_count;
}

int	compare_intersections(const void *a, const void *b)
{
	t_intersection	*ia;
	t_intersection	*ib;

	ia = (t_intersection *)a;
	ib = (t_intersection *)b;
	if (ia->t < ib->t)
		return (-1);
	else if (ia->t > ib->t)
		return (1);
	else
		return (0);
}

void	sort_intersections(t_intersections *intersections)
{
	qsort(intersections->intersections, intersections->count,
		sizeof(t_intersection), compare_intersections);
}

t_intersections	intersect_world(t_world *world, t_ray r)
{
	t_sphere		*s;
	t_intersections	sphere_xs;

	t_intersections xs = {0, 0};
	for (int i = 0; i < world->object_count; i++)
	{
		s = world->objects[i].data;
		sphere_xs = intersect(s, r);
		// printf("sphere_xs.count = %d\n", sphere_xs.count);
		for (int j = 0; j < sphere_xs.count; j++)
		{
			add_intersection(&xs, sphere_xs.intersections[j].t, s);
		}
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

