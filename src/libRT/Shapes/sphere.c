/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/02 11:23:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	sphere(void);
void		set_transform(t_sphere *s, t_matrix t);
t_tuple		normal_at(t_sphere sphere, t_tuple p);

t_sphere	sphere(void)
{
	t_sphere	s;

	s.center = point(0, 0, 0);
	s.radius = 1;
	s.transform = identity_matrix();
	s.material = material();
	s.motif = NULL;
	s.scale = point(1, 1, 1);
	return (s);
}

void	set_transform(t_sphere *s, t_matrix t)
{
	if (s != NULL)
		s->transform = t;
}

t_tuple	normal_at(t_sphere sphere, t_tuple p)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = multiply_matrix_tuple(inverse(sphere.transform), p);
	object_normal = subtract_tuples(object_point, (t_tuple){sphere.center.x,
			sphere.center.y, sphere.center.z, 1});
	world_normal = multiply_matrix_tuple(transpose_matrix(inverse(sphere.transform)),
			object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_intersections intersect_sphere(t_sphere *s, t_ray r)
{
    t_matrix inverse_transform = inverse(s->transform);
    t_ray transformed_ray = transform(r, inverse_transform);
    t_tuple sphere_to_ray = subtract_tuples(transformed_ray.origin, s->center);

    double a = dot(transformed_ray.direction, transformed_ray.direction);
    double b = 2.0 * dot(transformed_ray.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - (s->radius * s->radius);

    double discriminant = b * b - 4 * a * c;

    t_intersections xs;
    if (discriminant < 0)
    {
        xs.count = 0;
        xs.intersections = NULL;
    }
    else
    {
        xs.count = (discriminant == 0) ? 2 : 2;
        xs.intersections = ft_calloc(xs.count, sizeof(t_intersection));
        if (xs.intersections == NULL) exit(EXIT_FAILURE);

        double root = sqrt(discriminant);

        double t1 = (-b - root) / (2 * a);
        double t2 = (-b + root) / (2 * a);

        if (t1 > t2) {
            double temp = t1;
            t1 = t2;
            t2 = temp;
        }

        xs.intersections[0].t = t1;
        xs.intersections[0].object.sphere = s;
        xs.intersections[0].type = SPHERE;

        if (discriminant == 0) {
            xs.intersections[1].t = t1;
        } else {
            xs.intersections[1].t = t2;
        }
        xs.intersections[1].object.sphere = s;
        xs.intersections[1].type = SPHERE;
    }
    return xs;
}

