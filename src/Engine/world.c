/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:07:18 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/27 17:39:30 by svolodin         ###   ########.fr       */
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
	xs->intersections[xs->count].type = SPHERE;
	xs->count = new_count;
}


void	add_intersection_plane(t_intersections *xs, double t, t_plane *p)
{
	int	new_count;

	new_count = xs->count + 1;
	xs->intersections = realloc(xs->intersections, new_count
			* sizeof(t_intersection));
	if (xs->intersections == NULL)
		exit(EXIT_FAILURE);
	xs->intersections[xs->count].t = t;
	xs->intersections[xs->count].plane = p;
	xs->intersections[xs->count].type = PLANE;
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
	t_plane			*p;
	t_intersections	sphere_xs;
	t_intersections	plane_xs;

	t_intersections xs = {0, 0};
	for (int i = 0; i < world->object_count; i++)
	{
		if (world->objects[i].type == SPHERE)
		{
			s = world->objects[i].data;
			sphere_xs = intersect(s, r);
			for (int j = 0; j < sphere_xs.count; j++)
			{
				add_intersection(&xs, sphere_xs.intersections[j].t, s);
			}
		}
		if (world->objects[i].type == PLANE)
		{
			p = world->objects[i].data;
			plane_xs = local_intersect_plane(p, r);
			if (plane_xs.count)
				add_intersection_plane(&xs, 1, p);
		}
	}
	sort_intersections(&xs);
	return (xs);
}

t_comps prepare_computations(t_intersection i, t_ray r)
{
    t_comps comps;
    comps.t = i.t;
    comps.point = position(r, comps.t);
    comps.eyev = negate_tuple(r.direction);

	if (i.type == SPHERE)
	{
		t_sphere *sphere = (t_sphere *)i.sphere;
		comps.normalv = normal_at(*sphere, comps.point);
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
	}
	else if (i.type == PLANE)
	{
		t_plane *plane = (t_plane *)i.plane;
		comps.normalv = local_normal_at_plane(*plane, comps.point);
	}

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
	t_color result = color(0, 0, 0);
	if (i->type == SPHERE)
		result = shade_hit(w, comps);
	else if (i->type == PLANE)
	{
		result = i->plane->material.color;
		printf("Intersection avec plane\n");
	}	
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

