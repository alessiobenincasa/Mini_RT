/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:32:48 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/29 15:32:23 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersections local_intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
    t_intersections xs;
    xs.count = 0;
    xs.intersections = NULL;
    double a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);

    if (fabs(a) > EPSILON)
    {
        double b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
        double c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
        double disc = b * b - 4 * a * c;

        if (disc >= 0)
        {
            double t0 = (-b - sqrt(disc)) / (2*a);
            double t1 = (-b + sqrt(disc)) / (2*a);
            if (t0 > t1) { double temp = t0; t0 = t1; t1 = temp; }

            double y0 = ray.origin.y + t0 * ray.direction.y;
            if (y0 > cyl->minimum && y0 < cyl->maximum)
                add_intersection_cylinder(&xs, t0, cyl);

            double y1 = ray.origin.y + t1 * ray.direction.y;
            if (y1 > cyl->minimum && y1 < cyl->maximum)
                add_intersection_cylinder(&xs, t1, cyl);
        }
    }


    if (cyl->closed && fabs(ray.direction.y) > EPSILON)
    {
        double t_lower = (cyl->minimum - ray.origin.y) / ray.direction.y;
        if (check_cap(ray, t_lower, 1))
            add_intersection_cylinder(&xs, t_lower, cyl);
        double t_upper = (cyl->maximum - ray.origin.y) / ray.direction.y;
        if (check_cap(ray, t_upper, 1))
            add_intersection_cylinder(&xs, t_upper, cyl);
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
    cyl.minimum = -INFINITY;
    cyl.maximum = INFINITY;
    cyl.closed = 0;
    cyl.material = material();
    return cyl;
}

t_tuple local_normal_at_cylinder(t_cylinder cylinder, t_tuple point)
{
    double dist = pow(point.x, 2) + pow(point.z, 2);

    if (dist < 1 && point.y >= cylinder.maximum - EPSILON)
        return vector(0, 1, 0);
    else if (dist < 1 && point.y <= cylinder.minimum + EPSILON)
        return vector(0, -1, 0);
    else
        return vector(point.x, 0, point.z);
}

void add_intersection_cylinder(t_intersections *xs, double t, void *object)
{
    xs->count++;
    xs->intersections = realloc(xs->intersections, xs->count * sizeof(t_intersection));
    xs->intersections[xs->count - 1].t = t;
    xs->intersections[xs->count - 1].object = object;
}

t_cone cone(void)
{
    t_cone cone;
    cone.transform = identity_matrix();
    cone.minimum = -INFINITY;
    cone.maximum = INFINITY;
    cone.closed = 0;
    cone.material = material();
    return cone;
}
t_tuple local_normal_at_cone(t_cone cylinder, t_tuple point)
{
    (void)cylinder;
    double y = sqrt(pow(point.x, 2) + pow(point.z, 2));

    if (point.y > 0)
        y = -y;

    return vector(point.x, y, point.z);
}

int check_cap_cylinder(t_ray ray, double t, double y, int is_lower)
{
    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;
    double radius = (is_lower ? fabs(y - ray.origin.y) : fabs(y - (ray.origin.y + t * ray.direction.y)));
    return (x * x + z * z) <= (radius * radius);
}

t_intersections local_intersect_cone(t_cone *cyl, t_ray ray)
{
    t_intersections xs;
    xs.count = 0;
    xs.intersections = NULL;
    double a = pow(ray.direction.x, 2) - pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
    double b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y + 2 * ray.origin.z *ray.direction.z;
    double c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2) + pow(ray.origin.z, 2);
    double disc = b * b - 4 * a * c;
    
    if (fabs(a) < EPSILON && fabs(b) < EPSILON)
        return xs;
        
    if (disc >= 0)
    {
        double t0 = (-b - sqrt(disc)) / (2*a);
        double t1 = (-b + sqrt(disc)) / (2*a);
        if (t0 > t1) { double temp = t0; t0 = t1; t1 = temp; }

        double y0 = ray.origin.y + t0 * ray.direction.y;
        if (y0 > cyl->minimum && y0 < cyl->maximum)
            add_intersection_cylinder(&xs, t0, cyl);

        double y1 = ray.origin.y + t1 * ray.direction.y;
        if (y1 > cyl->minimum && y1 < cyl->maximum)
            add_intersection_cylinder(&xs, t1, cyl);
    }


    if (cyl->closed && fabs(ray.direction.y) > EPSILON)
    {
        double t_lower = (cyl->minimum - ray.origin.y) / ray.direction.y;
        if (check_cap_cylinder(ray, t_lower, cyl->minimum, 1))
            add_intersection_cylinder(&xs, t_lower, cyl);
        double t_upper = (cyl->maximum - ray.origin.y) / ray.direction.y;
        if (check_cap_cylinder(ray, t_upper, cyl->maximum, 1))
            add_intersection_cylinder(&xs, t_upper, cyl);
    }

    if (fabs(a) < EPSILON && fabs(b) >= EPSILON)
    {
        double t = -c / (2 * b);
        double y = ray.origin.y + t * ray.direction.y;
        if (cyl->minimum < y && y < cyl->maximum) {
            add_intersection_cylinder(&xs, t, cone);
        }
    }

    return xs;
}