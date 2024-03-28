/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/28 08:39:17 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersection	intersection(double t, t_sphere *object);
t_intersections	intersections(int count, t_intersection *inter_arr);
t_intersections	intersect(t_sphere *s, t_ray r);
t_intersection	*hit(t_intersections *xs);

t_intersection intersection(double t, t_sphere *object)
{
    t_intersection i;
    i.t = t;
    i.sphere = object;
    return i;
}

t_intersections intersections(int count, t_intersection *intersectionsArray)
{
    t_intersections xs;
    int i = 0;
    xs.count = count;
    xs.intersections = (t_intersection *)malloc(sizeof(t_intersection) * count);
    while (i < count)
    {
        xs.intersections[i] = intersectionsArray[i];
        i++;
    }
    return xs;
}

t_intersections intersect(t_sphere *s, t_ray r)
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
        xs.intersections = malloc(xs.count * sizeof(t_intersection));
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
        xs.intersections[0].sphere = s;
        xs.intersections[0].type = SPHERE;

        if (discriminant == 0) {
            xs.intersections[1].t = t1;
        } else {
            xs.intersections[1].t = t2;
        }
        xs.intersections[1].sphere = s;
        xs.intersections[1].type = SPHERE;
    }
    return xs;
}


t_intersection *hit(t_intersections *intersections)
{
    int i = 0;
    t_intersection *hit = NULL;
    while (i < intersections->count)
    {
        if (intersections->intersections[i].t >= 0)
        {
            if (hit == NULL || intersections->intersections[i].t < hit->t)
                hit = &(intersections->intersections[i]);
        }
        i++;
    }
    return (hit);
}
