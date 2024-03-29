/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cap_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:16:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/29 14:03:57 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	orientation_incorrect(t_tuple orientation)
{
	if (orientation.x < -1 || orientation.x > 1)
		return (1);
	else if (orientation.y < -1 || orientation.y > 1)
		return (2);
	else if (orientation.z < -1 || orientation.z > 1)
		return (3);
	return (0);
}

static int	add_amblight_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	get_next_value(&value, &line);
	
	scene_data->ambient_light->ratio = ft_atof(value);
	free(value);
	if (scene_data->ambient_light->ratio < 0
		|| scene_data->ambient_light->ratio > 1)
	{
		return (error("Ambient light ratio incorrect"), 1);
	}
	get_next_value(&value, &line);
	if (parse_colors(value, &(scene_data->ambient_light->color)) != 0)
	{
		free(value);
		return (error("Incorrect RGB values for ambient light"), 1);
	}
	free(value);
	scene_data->initialised.ambient_light = 1;
	return (0);
}

static int	add_camera_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	get_next_value(&value, &line);
	parse_coordinates(value, &(scene_data->camera->position));
	print_tuple(scene_data->camera->position);
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(scene_data->camera->orientation));
	free(value);
	if (orientation_incorrect(scene_data->camera->orientation))
		return (error("Orientation Incorrect"), 1);
	get_next_value(&value, &line);
	scene_data->camera->fov = ft_atof(value);
	free(value);
	if (scene_data->camera->fov < 0 || scene_data->camera->fov > 180)
		return (error("FOV Incorrect"), 1);
	scene_data->initialised.camera = 1;
	return (0);
}

static int	add_light_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	initialize_scene_light(scene_data);
	get_next_value(&value, &line);
	parse_coordinates(value, &(scene_data->light->position));
	free(value);
	get_next_value(&value, &line);
	scene_data->light->energy = ft_atof(value);
	free(value);
	if (scene_data->light->energy < 0 || scene_data->light->energy > 1)
		return (error("Light intensity value incorrect"), 1);
	get_next_value(&value, &line);
	if (parse_colors(value, &(scene_data->light->intensity)) != 0)
	{
		free(value);
		return (error("Incorrect RGB values for light"), 1);
	}
	free(value);
	scene_data->initialised.light = 1;
	return (0);
}

int	add_capital_element(t_identifier_type type, t_scene_data *scene_data,
		char *line)
{
	if (type == AMBIENT_LIGHT)
	{
		if (scene_data->initialised.ambient_light)
			return (error("Multiple Ambient light elements detected"), 1);
		if (add_amblight_to_list(scene_data, line) != 0)
			return (error("Failed to add ambient light to list"), 1);
	}
	else if (type == CAMERA)
	{
		if (scene_data->initialised.camera)
			return (error("Multiple Camera elements detected"), 1);
		if (add_camera_to_list(scene_data, line) != 0)
			return (error("Failed to add camera to list"), 1);
	}
	else if (type == LIGHT)
	{
		if (scene_data->initialised.light)
			return (error("Multiple Light elements detected"), 1);
		if (add_light_to_list(scene_data, line) != 0)
			return (error("Failed to add light to list"), 1);
	}
	return (0);
}
