/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cap_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:16:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	add_amblight_to_list(t_scene_data *s, char *line)
{
	char	*value;

	value = NULL;
	if (get_float_val(value, &line, &(s->ambient_light->ratio)))
		return (error("Problem getting FOV"), 1);
	if (s->ambient_light->ratio < 0 || s->ambient_light->ratio > 1)
		return (error("Ambient light ratio incorrect"), 1);
	if (parse_colors(value, &line, &(s->ambient_light->color)) != 0)
		return (error("Incorrect RGB values for ambient light"), 1);
	s->initialised.ambient_light = 1;
	return (0);
}

int	add_camera_to_list(t_scene_data *s, char *line)
{
	char	*value;

	value = NULL;
	if (get_coordinates(value, &line, &(s->camera->position)))
		return (error("Problem getting coordinates"), 1);
	if (get_coordinates(value, &line, &(s->camera->orientation)))
		return (error("Problem getting orientation"), 1);
	if (check_oneone(s->camera->orientation))
		return (error("Orientation Incorrect"), 1);
	if (get_float_val(value, &line, &(s->camera->fov)))
		return (error("Problem getting FOV"), 1);
	if (s->camera->fov < 0 || s->camera->fov > 180)
		return (error("FOV Incorrect"), 1);
	s->initialised.camera = 1;
	return (0);
}

int	add_light_to_list(t_scene_data *s, char *line)
{
	char	*value;

	value = NULL;
	s->light = initialize_scene_light();
	if (get_coordinates(value, &line, &(s->light->position)))
		return (error("Problem getting coordinates"), 1);
	if (get_float_val(value, &line, &(s->light->energy)))
		return (error("Problem getting energy"), 1);
	if (s->light->energy < 0 || s->light->energy > 1)
		return (error("Light intensity value incorrect"), 1);
	if (parse_colors(value, &line, &(s->light->intensity)) != 0)
		return (error("Incorrect RGB values for light"), 1);
	s->initialised.light = 1;
	return (0);
}
