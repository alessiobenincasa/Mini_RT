/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:32:48 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/31 18:59:16 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersections local_intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
    t_intersections xs;
    xs.count = 0;
    xs.intersections = NULL;

    double radius = cyl->diameter / 2;
    t_ray tr_ray = transform(ray, inverse(cyl->transform));
    
    double a = pow(tr_ray.direction.x, 2) + pow(tr_ray.direction.z, 2);
    if (fabs(a) > EPSILON) {
        double b = 2 * tr_ray.origin.x * tr_ray.direction.x + 2 * tr_ray.origin.z * tr_ray.direction.z;
        double c = pow(tr_ray.origin.x, 2) + pow(tr_ray.origin.z, 2) - pow(radius, 2);
        double disc = b * b - 4 * a * c;

        if (disc >= 0) {
            double sqrt_disc = sqrt(disc);
            double t0 = (-b - sqrt_disc) / (2 * a);
            double t1 = (-b + sqrt_disc) / (2 * a);

            if (t0 > t1) {
                double temp = t0;
                t0 = t1;
                t1 = temp;
            }

            double y0 = tr_ray.origin.y + t0 * tr_ray.direction.y;
            if (y0 > cyl->minimum && y0 < cyl->maximum) {
                add_intersection_cylinder(&xs, t0, cyl);
            }
            double y1 = tr_ray.origin.y + t1 * tr_ray.direction.y;
            if (y1 > cyl->minimum && y1 < cyl->maximum) {
                add_intersection_cylinder(&xs, t1, cyl);
            }
        }
    }

    if (cyl->closed && fabs(tr_ray.direction.y) > EPSILON) {
        double t_lower = (cyl->minimum - tr_ray.origin.y) / tr_ray.direction.y;
        if (check_cap(tr_ray, t_lower, radius)) {
            add_intersection_cylinder(&xs, t_lower, cyl);
        }

        double t_upper = (cyl->maximum - tr_ray.origin.y) / tr_ray.direction.y;
        if (check_cap(tr_ray, t_upper, radius)) {
            add_intersection_cylinder(&xs, t_upper, cyl);
        }
    }

    return xs;
}

int check_cap(t_ray ray, double t, double radius)
{
    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;
    return (x*x + z*z) <= (radius * radius);
}

t_cylinder cylinder(void)
{
    t_cylinder cyl;
    cyl.transform = identity_matrix();
    cyl.minimum = 0;
    cyl.maximum = 3;
    cyl.closed = 1;
    cyl.material = material();
    cyl.material.specular = 0;
    cyl.material.diffuse = 0.6;
    cyl.material.shininess = 50;
    return cyl;
}

t_tuple local_normal_at_cylinder(t_cylinder cyl, t_tuple point)
{
    double radius = cyl.diameter / 2;
    double dist = pow(point.x, 2) + pow(point.z, 2);
    if (dist < pow(radius, 2) && point.y >= cyl.maximum - EPSILON)
        return vector(0, 1, 0);
    else if (dist < pow(radius, 2) && point.y <= cyl.minimum + EPSILON)
        return vector(0, -1, 0);
    else
        return vector(point.x, 0, point.z);
}

t_tuple normal_at_cylinder(t_cylinder cylinder, t_tuple p)
{
    t_tuple object_point = multiply_matrix_tuple(inverse(cylinder.transform), p);
    t_tuple object_normal = local_normal_at_cylinder(cylinder, object_point);
    t_tuple world_normal = multiply_matrix_tuple(transpose_matrix(inverse(cylinder.transform)), object_normal);
    world_normal.w = 0;

    return (normalize(world_normal));
}


void add_intersection_cylinder(t_intersections *xs, double t, t_cylinder *cyl)
{
    xs->count++;
    xs->intersections = realloc(xs->intersections, xs->count * sizeof(t_intersection));
    xs->intersections[xs->count - 1].t = t;
    xs->intersections[xs->count - 1].object.cylinder = cyl;
    xs->intersections[xs->count - 1].type = CYLINDER;
}
