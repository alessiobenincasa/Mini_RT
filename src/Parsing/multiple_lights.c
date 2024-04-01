/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:13:13 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/01 14:35:11 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_light	*get_extra_light(char *line)
{
	t_light	*l;
	char	*value;

	l = initialize_scene_light();
	if (!l)
		return (NULL);
	get_next_value(&value, &line);
	parse_coordinates(value, &(l->position));
	free(value);
	get_next_value(&value, &line);
	l->energy = ft_atof(value);
	free(value);
	if (l->energy < 0 || l->energy > 1)
		return (free(l), error("Light intensity value incorrect"), NULL);
	get_next_value(&value, &line);
	if (parse_colors(value, &(l->intensity)) != 0)
	{
		free(value);
		return (free(l), error("Incorrect RGB values for light"), NULL);
	}
	free(value);
	return (l);
}

int	add_extra_light(t_scene_data *scene_data, char *line)
{
	t_light	*light;
	t_list	*new_node;

	light = get_extra_light(line);
	if (!light)
		return (error("failed to get extra lights data"), 1);
	new_node = ft_lstnew(light);
	if (!new_node)
		return (free(light), 1);
	new_node->type = EXTRA_LIGHT;
	if (!scene_data->extra_lights)
		scene_data->extra_lights = new_node;
	else
		ft_lstadd_back(&(scene_data->extra_lights), new_node);
	return (0);
}
