/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:07:18 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/21 12:56:30 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_world	world(void)
{
	t_world	w;

	w.objects = NULL;
	w.object_count = 0;
	w.light = NULL;
	return (w);
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

// t_world default_world(void)
// {
	
//     t_world		w;
//     t_vector 	l = tuple_to_vector(vector(-10, 10, -10));
//     int     colors[3] = {1, 1, 1};
//     t_light light = point_light(l, 1, colors);

//     t_sphere s1 = sphere();
//     s1.material.color[0] = 0.8;
//     s1.material.color[1] = 1.0; 
//     s1.material.color[2] = 0.6;
//     s1.material.diffuse = 0.7;
//     s1.material.specular = 0.2;

//     t_sphere s2 = sphere();
//     s2.transform = scaling(0.5, 0.5, 0.5);

//     w.light = &light;
//     w.object_count = 2;
//     w.objects = malloc(sizeof(t_object) * 2);
//     w.objects[0].data = &s1;
//     w.objects[1].data = &s2;

//     return (w);
// }

t_intersections	intersect_world(t_world *world, t_ray r)
{
	t_sphere		*s;
	t_intersections	sphere_xs;

	t_intersections xs = {0, 0};
	for (int i = 0; i < world->object_count; i++)
	{
		s = world->objects[i].data;
		sphere_xs = intersect(s, r);
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
    if (dot(comps.normalv, comps.eyev) < 0)
    {
        comps.inside = 1;
        comps.normalv = negate_tuple(comps.normalv);
    }
    else
        comps.inside = 0;

    return (comps);
}

t_color shade_hit(t_world world, t_comps comps)
{
    return (lighting(comps.sphere->material, *world.light , comps.point, comps.eyev, comps.normalv));
}


