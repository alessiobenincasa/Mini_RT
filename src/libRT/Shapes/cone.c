/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:27:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 09:08:44 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_cone cone(void)
{
    t_cone cone;
    cone.transform = identity_matrix();
    cone.minimum = 0;
    cone.maximum = 3;
    cone.closed = 1;
    cone.inverted = 1;
    cone.material = material();
	cone.material.specular = 0;
    cone.material.diffuse = 0.6;
    cone.material.shininess = 50;
    return cone;
}
t_tuple local_normal_at_cone(t_cone cone, t_tuple point)
{
    double radius = cone.maximum / 2;
    double dist = pow(point.x, 2) + pow(point.z, 2);
    if (dist < pow(cone.maximum, 2) && point.y >= cone.maximum - EPSILON)
        return vector(0, 1, 0);
    else if (dist < pow(cone.maximum, 2) && point.y <= cone.minimum + EPSILON)
        return vector(0, -1, 0);
    else
    {
        double slantHeight = sqrt(pow(point.x, 2) + pow(point.z, 2));
        double height = fabs(cone.maximum - cone.minimum);
        double slope = radius / height;
        double y = slope * slantHeight;
        if (cone.inverted)
            y = -y;
        return (vector(point.x, y, point.z));
    }
}

t_tuple normal_at_cone(t_cone cone, t_tuple p)
{
    t_tuple object_point = mult_mat_tup(inverse(cone.transform), p);
    t_tuple object_normal = local_normal_at_cone(cone, object_point);
    t_tuple world_normal = mult_mat_tup(transpose_matrix(inverse(cone.transform)), object_normal);
    world_normal.w = 0;

    return (normalize(world_normal));
}

int check_cap_cone(t_ray ray, double t, t_cone *cone, int is_lower)
{
    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;
    double cap = is_lower ? cone->minimum : cone->maximum;
    return (x * x + z * z) <= (cap * cap);
}

void add_intersection_cone(t_intersections *xs, double t, t_cone *cone)
{
    xs->count++;
    xs->intersections = realloc(xs->intersections, xs->count * sizeof(t_intersection));
    xs->intersections[xs->count - 1].t = t;
    xs->intersections[xs->count - 1].object.cone = cone;
    xs->intersections[xs->count - 1].type = CONE;
}

t_intersections intersect_cone(t_cone *cone, t_ray r)
{
    t_intersections xs;
    xs.count = 0;
    xs.intersections = NULL;

	t_ray ray = transform(r, inverse(cone->transform));

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
        if (y0 > cone->minimum && y0 < cone->maximum)
            add_intersection_cone(&xs, t0, cone);

        double y1 = ray.origin.y + t1 * ray.direction.y;
        if (y1 > cone->minimum && y1 < cone->maximum)
            add_intersection_cone(&xs, t1, cone);
    }


    if (cone->closed && fabs(ray.direction.y) > EPSILON)
    {
        double t_lower = (cone->minimum - ray.origin.y) / ray.direction.y;
        if (check_cap_cone(ray, t_lower, cone, 1))
            add_intersection_cone(&xs, t_lower, cone);
        double t_upper = (cone->maximum - ray.origin.y) / ray.direction.y;
        if (check_cap_cone(ray, t_upper, cone, 0))
            add_intersection_cone(&xs, t_upper, cone);
    }

    if (fabs(a) < EPSILON && fabs(b) >= EPSILON)
    {
        double t = -c / (2 * b);
        double y = ray.origin.y + t * ray.direction.y;
        if (cone->minimum < y && y < cone->maximum) {
            add_intersection_cone(&xs, t, cone);
        }
    }

    return xs;
}

