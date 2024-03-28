/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:03:28 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/28 19:09:12 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersections local_intersect_cylinder(t_cylinder *cyl, t_ray r)
{
    t_intersections xs;
    xs.count = 0;
    xs.intersections = NULL;
    double a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
    if (fabs(a) < EPSILON)
        return xs;
        
    double b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    double c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1; 
    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return xs;
    
    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    xs.count = 2;
    xs.intersections = (t_intersection *)malloc(xs.count * sizeof(t_intersection));
    if (!xs.intersections)
        exit(EXIT_FAILURE); 
    
    if (t0 > t1)
    {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }
    xs.intersections[0].t = t0;
    xs.intersections[0].object = cyl; 
    xs.intersections[1].t = t1;
    xs.intersections[1].object = cyl;

    return xs;
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

