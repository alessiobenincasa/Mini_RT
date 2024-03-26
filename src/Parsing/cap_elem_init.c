/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap_elem_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:46:25 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/26 11:50:00 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	initialize_scene_light(t_scene_data *scene)
{
	if (scene == NULL)
		return ;
	scene->light = (t_light *)malloc(sizeof(t_light));
	if (scene->light != NULL)
	{
		scene->light->position = point(0.0, 0.0, 0.0);
		scene->light->intensity = color(0.0, 0.0, 0.0);
		scene->light->energy = 1.0;                            
	}
}
