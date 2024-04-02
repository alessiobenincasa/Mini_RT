/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:11:49 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 14:51:16 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int is_shadowed(t_world world, t_tuple point, t_tuple light_pos);

int is_shadowed(t_world world, t_tuple point, t_tuple light_pos)
{
    t_tuple v = subtract_tuples(light_pos, point);
    double distance = magnitude(v);
    t_tuple direction = normalize(v);

    t_ray r = ray(add_tuples(point, multiply_tuple_scalar(direction, EPSILON)), direction);
    t_intersections inters = intersect_world(&world, r);
    t_intersection* h = hit(&inters);
    if (h != NULL && h->t < distance)
        return (1);
    else 
        return (0);
}