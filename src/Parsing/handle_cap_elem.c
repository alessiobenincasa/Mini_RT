/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cap_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:43:20 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/02 16:43:32 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	handle_amb_light(t_scene_data *s, char *line)
{
	if (s->initialised.ambient_light)
		return (error("Multiple Ambient light elements detected"), 1);
	if (add_amblight_to_list(s, line) != 0)
		return (error("Failed to add ambient light to list"), 1);
	return (0);
}

static int	handle_cam(t_scene_data *s, char *line)
{
	if (s->initialised.camera)
		return (error("Multiple Camera elements detected"), 1);
	if (add_camera_to_list(s, line) != 0)
		return (error("Failed to add camera to list"), 1);
	return (0);
}

static int	handle_light(t_scene_data *s, char *line)
{
	if (s->initialised.light)
		return (error("Multiple Light elements detected"), 1);
	if (add_light_to_list(s, line) != 0)
		return (error("Failed to add light to list"), 1);
	return (0);
}

int	add_capital_element(t_id_type type, t_scene_data *scene_data, char *line)
{
	if (type == AMBIENT_LIGHT)
	{
		if (handle_amb_light(scene_data, line))
			return (1);
	}
	else if (type == CAMERA)
	{
		if (handle_cam(scene_data, line))
			return (2);
	}
	else if (type == LIGHT)
	{
		if (handle_light(scene_data, line))
			return (3);
	}
	else if (type == EXTRA_LIGHT)
	{
		if (add_extra_light(scene_data, line) != 0)
			return (error("Failed to add extra light to list"), 4);
	}
	return (0);
}
