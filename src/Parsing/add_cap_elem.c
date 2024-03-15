/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cap_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:16:03 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 16:42:56 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	orientation_incorrect(t_vector orientation)
{
	if (orientation.x < -1 || orientation.x > 1)
		return (1);
	else if (orientation.y < -1 || orientation.y > 1)
		return (2);
	else if (orientation.z < -1 || orientation.z > 1)
		return (3);
	return (0);
}

static int	add_camera_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	value = strdup_upto_whitespace(line);
	parse_coordinates(value, &(scene_data->camera.position));
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	value = strdup_upto_whitespace(line);
	parse_coordinates(value, &(scene_data->camera.orientation));
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	if (orientation_incorrect(scene_data->camera.orientation))
		return (error("Orientation Incorrect"), 1);
	value = strdup_upto_whitespace(line);
	scene_data->camera.fov = ft_atof(value);
	free(value);
	if (scene_data->camera.fov < 0 || scene_data->camera.fov > 180)
		return (error("FOV Incorrect"), 1);
	return (0);
}

static int	add_amblight_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	value = strdup_upto_whitespace(line);
	scene_data->ambient_light.ratio = ft_atof(value);
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	if (scene_data->ambient_light.ratio < 0
		|| scene_data->ambient_light.ratio > 1)
		return (error("Ambient light ratio incorrect"), 1);
	value = strdup_upto_whitespace(line);
	if (parse_colors(value, scene_data->ambient_light.color) != 0)
	{
		free(value);
		return (error("Incorrect RGB values for ambient light"), 1);
	}
	free(value);
	return (0);
}

static int	add_light_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	value = strdup_upto_whitespace(line);
	parse_coordinates(value, &(scene_data->light.position));
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	value = strdup_upto_whitespace(line);
	scene_data->light.intensity = ft_atof(value);
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	if (scene_data->light.intensity < 0 || scene_data->light.intensity > 1)
		return (error("Light intensity value incorrect"), 1);
	value = strdup_upto_whitespace(line);
	if (parse_colors(value, scene_data->light.color) != 0)
	{
		free(value);
		return (error("Incorrect RGB values for light"), 1);
	}
	free(value);
	return (0);
}

int	add_capital_element(t_identifier_type type, t_scene_data *scene_data,
		char *line)
{
	if (type == CAMERA)
	{
		if (add_camera_to_list(scene_data, line) != 0)
			return (error("Failed to add camera to list"), 1);
		print_camera(&(scene_data->camera));
	}
	if (type == AMBIENT_LIGHT)
	{
		if (add_amblight_to_list(scene_data, line) != 0)
			return (error("Failed to add ambient light to list"), 1);
		print_ambient(&(scene_data->ambient_light));
	}
	if (type == LIGHT)
	{
		if (add_light_to_list(scene_data, line) != 0)
			return (error("Failed to add light to list"), 1);
		print_light(&(scene_data->light));
	}
	return (0);
}
