/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:46:25 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_light	*initialize_scene_light(void)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = point(0.0, 0.0, 0.0);
	light->intensity = color(0.0, 0.0, 0.0);
	light->energy = 1.0;
	return (light);
}
