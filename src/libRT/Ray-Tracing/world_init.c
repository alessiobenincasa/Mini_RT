/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 12:04:39 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_world	world(void);
t_world	default_world(void);
void	free_world(t_world *w);

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
