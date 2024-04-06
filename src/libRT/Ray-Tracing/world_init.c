/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 10:44:31 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_world	world_init(void);

t_world	world_init(void)
{
	t_world	w;
	t_light	l;

	l.energy = 1;
	l.intensity = color(255, 255, 255);
	l.position = point(42, 42, 42);
	w.objects = NULL;
	w.object_count = 0;
	w.light = l;
	w.extra_lights = NULL;
	return (w);
}

int	no_world_light(t_light l)
{
	return (l.position.x == 42 && l.position.y == 42 && l.position.z == 42);
}
