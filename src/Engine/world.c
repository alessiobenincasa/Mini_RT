/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:07:18 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/20 12:07:34 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_world world(void)
{
    t_world w;
    w.objects = NULL;   
    w.object_count = 0; 
    w.light = NULL;    
    return w;
}


void add_intersection(t_intersections* xs, double t, t_sphere* s)
{
    int new_count = xs->count + 1;
    xs->intersections = realloc(xs->intersections, new_count * sizeof(t_intersection));
    if (xs->intersections == NULL)
        exit(EXIT_FAILURE);
    
    xs->intersections[xs->count].t = t;
    xs->intersections[xs->count].sphere = s;
    xs->count = new_count;
}

int compare_intersections(const void* a, const void* b)
{
    t_intersection* ia = (t_intersection*)a;
    t_intersection* ib = (t_intersection*)b;

    if (ia->t < ib->t)
        return -1;
    else if (ia->t > ib->t)
        return 1;
    else
        return 0;
}

void sort_intersections(t_intersections* intersections)
{
    qsort(intersections->intersections, intersections->count, sizeof(t_intersection), compare_intersections);
}

t_intersections intersect_world(t_world* world, t_ray r)
{
    t_intersections xs = {0, 0};
    for (int i = 0; i < world->object_count; i++)
    {
        t_sphere* s = world->objects[i].data;
        t_intersections sphere_xs = intersect(s, r);
        for (int j = 0; j < sphere_xs.count; j++) {
            add_intersection(&xs, sphere_xs.intersections[j].t, s);
        }
    }
    sort_intersections(&xs);
    for (int k = 0; k < xs.count; k++)
    {
        printf("intesection : %f\n", xs.intersections[k].t);
    }
    return xs;
}
